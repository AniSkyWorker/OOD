#pragma once
#include <boost\signals2.hpp>
#include <initializer_list>

using Connection = boost::signals2::connection;
using ScopedConnection = boost::signals2::scoped_connection;

using SharedConnectionBlock = boost::signals2::shared_connection_block;

template <typename Signature>
using Signal = boost::signals2::signal<Signature>;

using EmptySignal = Signal<void()>;

template <typename SlotType, typename SelfType, typename... Ts>
SlotType TrackSlot(const std::shared_ptr<SelfType> & obj, Ts&&... args)
{
	return SlotType(std::forward<Ts>(args)...).track_foreign(obj);
}

template <typename T>
struct EnableSelfTracking : public std::enable_shared_from_this<T>
{
protected:
	template <typename SlotType, typename... Ts>
	SlotType TrackSelf(Ts&&... args)
	{
		return TrackSlot<SlotType>(shared_from_this(), std::forward<Ts>(args)...);
	}
};

struct ScopedConnectionsStorage
{
	ScopedConnectionsStorage& operator+=(const Connection & conn)
	{
		m_items.emplace_back(conn);
		return *this;
	}
	ScopedConnectionsStorage& operator+=(Connection && conn)
	{
		m_items.emplace_back(std::move(conn));
		return *this;
	}
	ScopedConnectionsStorage& operator+=(ScopedConnection && conn)
	{
		m_items.emplace_back(std::move(conn));
		return *this;
	}
	ScopedConnectionsStorage& operator += (std::initializer_list<Connection> const & connections)
	{
		for (const auto & con : connections)
		{
			*this += con;
		}
		return *this;
	}
private:
	std::vector<ScopedConnection> m_items;
};