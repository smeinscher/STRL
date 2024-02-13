//
// Created by Sterling on 2/12/2024.
//

#ifndef ISTRLSUBJECT_H
#define ISTRLSUBJECT_H

#include "ISTRLObserver.h"

namespace strl
{

template <typename MESSAGE_TYPE>
class ISTRLSubject
{
public:
	virtual ~ISTRLSubject() = default;
	virtual void attach(ISTRLObserver<MESSAGE_TYPE>* observer) = 0;
	virtual void detach(ISTRLObserver<MESSAGE_TYPE>* observer) = 0;
	virtual void notify(MESSAGE_TYPE& message) = 0;
};

} // strl

#endif //ISTRLSUBJECT_H
