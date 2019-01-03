/*
 * Created by Yves Gingras on 2018-12-12.
 */

#ifndef CHAPTER17_TRYTHIS_H
#define CHAPTER17_TRYTHIS_H

#include <string>

class Try1752 {
public:
	Try1752();
	virtual ~Try1752();


private:
	std::string mName{"Try1752"};
};


class Try1752A : public Try1752 {
public:
	Try1752A();
	~Try1752A() override;


private:
	std::string mName{"Try1752A"};
};


#endif //CHAPTER17_TRYTHIS_H
