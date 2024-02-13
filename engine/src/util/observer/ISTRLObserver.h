//
// Created by Sterling on 2/12/2024.
//

#ifndef ISTRLOBSERVER_H
#define ISTRLOBSERVER_H

namespace strl
{

template <typename MESSAGE_TYPE>
class ISTRLObserver
{
public:
	virtual ~ISTRLObserver() = default;
	virtual void update(const MESSAGE_TYPE& type) = 0;
};

} // strl

#endif //ISTRLOBSERVER_H
