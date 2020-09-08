
#include "IKControleLeg.h"

using namespace ci;
using namespace ci::app;
using namespace std;

IKControleLegRef IKControleLeg::create()
{
	IKControleLegRef ref = std::make_shared<IKControleLeg>();
	return ref;
}