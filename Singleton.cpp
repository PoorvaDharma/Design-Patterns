// Program to implement Singleton Design Pattern

#include <iostream>
#include <mutex>
#include <thread> 

namespace DesignPattern
{
	class Singleton
	{
	private:

		int data;
		static std::mutex m;                                      //thread safe 

		Singleton() noexcept
			: data{ 0 } {
			std::cout << "constr called"<<std::endl;
		}

		static Singleton* SingleInstance;

	public:

		//delete copy ctor and copy assignment operator 
		//disallow copy
		Singleton& operator=(const Singleton & S) = delete;
		Singleton(const Singleton & S) = delete;                 // const in parameter applies to S, cannot change value of object using S

	                                                                //  const after the function name applies to this pointer, should be used with member functions, can be called by const/nonconst objects

		Singleton& operator=(const Singleton && S) = delete;
		Singleton(const Singleton && S) = delete;

		~Singleton() = default;                                //alwz called at program termiantion
		 

		static Singleton* getInstance()
		{
			std::lock_guard<std::mutex> guard(m);          //exceptionsafe 
			if (!SingleInstance)
				SingleInstance = new Singleton();

			return SingleInstance;
		}

		int getdata()
		{
			return this->data;
		}

		void setdata(int d)
		{
			this->data = d;
		}
	};

	Singleton* Singleton::SingleInstance = nullptr;
	std::mutex Singleton::m;
}


void f1()
{
	using namespace DesignPattern;
	using namespace std;

	std::thread::id thread_id = std::this_thread::get_id();
	std::cout << thread_id << "  "<<endl;
	
	std::cout << "in F1\n"<<endl;
	Singleton* s = Singleton::getInstance();
	s->setdata(500);
	std::cout <<s->getdata()<<endl;                                      //cout is not thread safe can be accessed in random order by any thread.
 }

int main()
{
	std::cout << "main" << std::endl;

	using namespace DesignPattern;
	
	std::thread t1(f1);

	std::thread t2(f1);

	t1.join();
	t2.join();

	
	Singleton* s1 = Singleton::getInstance();
	Singleton* s2 = Singleton::getInstance();
	s1->setdata(100);
	std::cout << s2->getdata()<<std::endl;



	std::cout << "out main" << std::endl;
	return 0;
}
