//
// Created by Sterling on 2/12/2024.
//

#ifndef STRLMANAGERBASE_H
#define STRLMANAGERBASE_H

#include <vector>
#include <memory>
#include <algorithm>

namespace strl
{

template<typename TYPE>
class STRLManagerBase
{
public:
	virtual ~STRLManagerBase() = default;

	template <typename DERIVED = TYPE, typename... ARGS>
	TYPE* create(ARGS... args)
	{
		std::unique_ptr<TYPE> item = std::make_unique<DERIVED>(args...);
		items_.emplace_back(std::move(item));
		return items_.back().get();
	}

	virtual std::vector<TYPE*> get_by_name(std::string_view name)
	{
		std::vector<TYPE*> objects_with_name;
		for (const auto& item : items_)
		{
			if (name == item->get_name())
			{
				objects_with_name.emplace_back(item.get());
			}
		}
		return objects_with_name;
	}

	virtual std::vector<TYPE*> get_by_tag(std::string_view tag)
	{
		std::vector<TYPE*> objects_with_tag;
		for (const auto& item : items_)
		{
			auto it = std::find(item->get_tags().begin(), item->get_tags().end(), tag);
			if (it != item->get_tags().end())
			{
				objects_with_tag.emplace_back(item.get());
			}
		}
		return objects_with_tag;
	}

	virtual TYPE* get_by_id(int id)
	{
		auto pred = [id](const std::unique_ptr<TYPE>& item)
		{
			return id == item->get_id();
		};
		auto it = std::find_if(items_.begin(), items_.end(), pred);
		if (it != items_.end())
		{
			return (*it).get();
		}
		return nullptr;
	}

	virtual const std::vector<std::unique_ptr<TYPE>>& get_all() const
	{
		return items_;
	}

	virtual void remove(TYPE* item)
	{
		auto pred = [item](const std::unique_ptr<TYPE>& i)
		{
			return item == i.get();
		};
		auto it = std::find_if(items_.begin(), items_.end(), pred);
		if (it != items_.end())
		{
			items_.erase(it);
		}
	}

	virtual void remove_multiple(const std::vector<TYPE*>& items)
	{
		for (auto item : items)
		{
			remove(item);
		}
	}

	virtual void remove_all()
	{
		items_.clear();
	}

	virtual std::vector<std::unique_ptr<TYPE>>::iterator begin()
	{
		return items_.begin();
	}

	virtual std::vector<std::unique_ptr<TYPE>>::iterator end()
	{
		return items_.end();
	}

protected:
	std::vector<std::unique_ptr<TYPE>> items_;
};

} // strl

#endif //STRLMANAGERBASE_H
