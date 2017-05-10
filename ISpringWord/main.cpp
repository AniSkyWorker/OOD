#include "stdafx.h"
#include "Menu.h"
#include "Document.h"
#include "PositionErrors.h"

using namespace std;
using namespace std::placeholders;
using namespace boost::filesystem;

namespace
{
constexpr char END[] = "end";
boost::optional<size_t> ReadParagraphPosition(istream & in, bool indexOnly = false)
{
    try
    {
        size_t position;
        in >> position;
        return position;
    }
    catch (const ios::failure&)
    {
        if (indexOnly)
        {
            throw UnexpectedPosition();
        }

        in.clear();
        string end;
        in >> end;
        if (end != END)
        {
            throw UnexpectedPosition(END);
        }
        return boost::none;
    }
}

class CEditor
{
public:
	CEditor()  //-V730
		:m_document(make_unique<CDocument>())
	{
		m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
		m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
		AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
        AddMenuItem("insertParagraph", "Insert paragraph at position. Args: <position> <paragraphText>", &CEditor::InsertParagraph);
        AddMenuItem("insertImage", "Add image at positions. Args: <position>|end <path> <width> <height>", &CEditor::InsertImage);
        AddMenuItem("deleteItem", "Delete item at position. Args: <position>", &CEditor::DeleteItem);
        AddMenuItem("replaceText", "Replace text at position. Args: <position> <newText>", &CEditor::ReplaceText);
        AddMenuItem("resizeImage", "Resize image at position. Args: <position> <width> <height>", &CEditor::ResizeImage);
        m_menu.AddItem("list", "Show document", bind(&CEditor::List, this, _1));
		AddMenuItem("undo", "Undo command", &CEditor::Undo);
		AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
        AddMenuItem("save", "Save html document to path. Args: <path>", &CEditor::Save);
	}

	void Start()
	{
		m_menu.Run();
	}

private:
	// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::*MenuHandler)(istream & in);

	void AddMenuItem(const string & shortcut, const string & description, MenuHandler handler)
	{
		m_menu.AddItem(shortcut, description, bind(handler, this, _1));
	}

	void SetTitle(istream & in)
	{
		string title;
		getline(in >> ws, title);
		m_document->SetTitle(title);
	}

    void InsertParagraph(istream & in)
    {
        try
        {
            auto pos = ReadParagraphPosition(in);
            string text;
            getline(in, text);
            m_document->InsertParagraph(text, pos);
        }
        catch (const exception & e)
        {
            cout << "Error while inserting paragraph:\n\t" << e.what() << endl;
        }
    }

    void CEditor::InsertImage(istream & in)
    {
        try
        {
            string args;
            getline(in, args);
            stringstream strStream(args);
            strStream.exceptions(istream::failbit);

            auto position = ReadParagraphPosition(strStream);

            string path;
            strStream >> path;

            unsigned width;
            strStream >> width;

            unsigned height;
            strStream >> height;

            m_document->InsertImage(path, width, height, position);
        }
        catch (const exception & e)
        {
            cout << "Error while inserting image:\n\t" << e.what() << endl;
        }
    }

    void CEditor::DeleteItem(istream & in)
    {
        try
        {
            auto pos = ReadParagraphPosition(in, true);
            m_document->DeleteItem(*pos);
        }
        catch (const exception & e)
        {
            cout << "Delete item error:\n\t" << e.what() << endl;
        }
    }

    void CEditor::ReplaceText(istream & in)
    {
        try
        {
            auto pos = ReadParagraphPosition(in, true);
            string text;
            getline(in, text);

            auto item = m_document->GetItem(*pos);
            if (auto paragraph = item.GetParagraph())
            {
                paragraph->SetText(text);
               
            }
            else
            {
                throw logic_error("Item not contains text");
            }
            
        }
        catch (const exception & e)
        {
            cout << "Replace text error:\n\t"  << e.what() << endl;
        }
    }

    void CEditor::ResizeImage(istream & in)
    {
        try
        {
            auto pos = ReadParagraphPosition(in, true);

            unsigned width;
            in >> width;

            unsigned height;
            in >> height;

            auto item = m_document->GetItem(*pos);
            if (auto image = item.GetImage())
            {
                image->Resize(width, height);
            }
            else
            {
                throw invalid_argument("Item not contains image");
            }
        }
        catch (const exception & e)
        {
            cout << "Resize image error:\n\t" << e.what() << endl;
        }
    }

	void List(istream &) const
	{
		cout << "-------------" << endl;
		cout << m_document->GetTitle() << endl;
        for (size_t i = 0; i < m_document->GetItemsCount(); i++)
        {
            auto& item = m_document->GetItem(i);
            if (auto paragraph = item.GetParagraph())
            {
                cout << i << ". Paragraph: " << paragraph->GetText() << endl;
            }
            else if(auto image = item.GetImage())
            {
                cout << i << ". Image: " << image->GetWidth() << "x" << image->GetHeight() << " " << path(image->GetPath()).filename() << endl;
            }
        }
        cout << "-------------" << endl;
	}

	void Undo(istream &)
	{
		if (m_document->CanUndo())
		{
			m_document->Undo();
		}
		else
		{
			cout << "Can't undo" << endl;
		}
	}

	void Redo(istream &)
	{
		if (m_document->CanRedo())
		{
			m_document->Redo();
		}
		else
		{
			cout << "Can't redo" << endl;
		}
	}

    void Save(istream & in)
    {
        try
        {
            string savePath;
            in >> savePath;
            m_document->Save(savePath);
        }
        catch (const exception & e)
        {
            cout << e.what() << endl;
        }
    }

	CMenu m_menu;
	unique_ptr<IDocument> m_document;
};

}

int main()
{
	CEditor editor;
	editor.Start();
	return 0;
}

