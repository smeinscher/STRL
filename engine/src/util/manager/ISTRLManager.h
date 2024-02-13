//
// Created by Sterling on 2/12/2024.
//

#ifndef ISTRLMANAGER_H
#define ISTRLMANAGER_H

#include <vector>
#include <memory>

namespace strl
{

template<typename TYPE, typename DEFINITION>
class ISTRLManager
{
public:
	virtual ~ISTRLManager() = default;
	virtual TYPE* create(DEFINITION& definition) = 0;
	virtual std::vector<TYPE*> get_by_name(const std::string& name) = 0;
	virtual std::vector<TYPE*> get_by_tag(const std::string& tag) = 0;
	virtual TYPE* get_by_id(int id) = 0;
	virtual const std::vector<std::pair<int&, std::unique_ptr<TYPE>>>& get_all() const = 0;
	virtual void remove(TYPE* item) = 0;
	virtual void remove_multiple(const std::vector<TYPE*>& item) = 0;

protected:
	// TODO: is this bad?
	std::vector<std::pair<int&, std::unique_ptr<TYPE>>> items_;
};

} // strl

#endif //ISTRLMANAGER_H
