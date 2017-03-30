#include "stdafx.h"
#include "Client.h"
#include "Designer.h"
#include "Painter.h"
#include "ShapeFactory.h"
#include <fstream>

namespace
{
const unsigned READ_FROM_FILE_ARG_COUNT = 2;

void InitPictureFromLayout(CClient & client, const std::string & filename)
{
    std::ifstream file(filename);
    client.CreatePicture(file);
}
}

int main(int argc, char ** argv)
{
    try
    {
        CDesigner designer(std::move(std::make_unique<CShapeFactory>()));
        CPainter painter;
        CClient client(designer, painter);
        switch(argc)
        {
        case READ_FROM_FILE_ARG_COUNT:
            InitPictureFromLayout(client, argv[READ_FROM_FILE_ARG_COUNT - 1]);
            break;
        default:
            client.CreatePicture(std::cin);
            break;
        }
    }
    catch (const std::exception & exc)
    {
        std::cout << "Error! " <<exc.what() << std::endl;
    }
}