//
// Created by Sterling on 2/12/2024.
//

#ifndef STRLSUBJECTBASE_H
#define STRLSUBJECTBASE_H

#include <vector>
#include <algorithm>
#include "ISTRLObserver.h"

namespace strl
{

template <typename MESSAGE_TYPE>
class STRLSubjectBase
{
public:
	virtual ~STRLSubjectBase() = default;

	virtual void attach(ISTRLObserver<MESSAGE_TYPE>* observer)
	{
		observers_.emplace_back(observer);
	}

	virtual void detach(ISTRLObserver<MESSAGE_TYPE>* observer)
	{
		auto it = std::find(observers_.begin(), observers_.end(), observer);
		if (it != observers_.end())
		{
			observers_.erase(it);
		}
	}

	virtual void notify(MESSAGE_TYPE& message)
	{
		for (auto observer : observers_)
		{
			observer->update(message);
		}
	}

private:
	std::vector<ISTRLObserver<MESSAGE_TYPE>*> observers_;
};

} // strl

#endif //STRLSUBJECTBASE_H
