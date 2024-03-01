//
// Created by SterlingMeinscher on 2/15/2024.
//

#ifndef STRLMANAGEDITEMBASE_H
#define STRLMANAGEDITEMBASE_H

#include <string>
#include <vector>

namespace strl
{

struct STRLManagedItemDefinitionBase
{
	std::string name;
	std::vector<std::string> tags;
};

class STRLManagedItemBase
{
public:
	STRLManagedItemBase(std::string name, std::vector<std::string> tags);

	[[nodiscard]] std::string_view get_name() const;
	void set_name(std::string name);

	[[nodiscard]] const std::vector<std::string>& get_tags() const;
	void add_tag(std::string tag);
	void remove_tag(std::string_view tag);

	[[nodiscard]] int get_id() const;

protected:
	std::string name_;
	std::vector<std::string> tags_;
	int id_;

private:
	// TODO: find a thread-safe method of assigning IDs to objects
	// TODO: replace with GUID
	static int id_accumulator_;
};

} // strl

#endif //STRLMANAGEDITEMBASE_H
