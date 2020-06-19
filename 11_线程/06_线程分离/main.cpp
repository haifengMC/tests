//detach: Detach �̡߳� ����ǰ�̶߳����������ִ��ʵ������̶߳�����룬ʹ���̵߳�ִ�п��Ե������С�һ���߳�ִ����ϣ������������Դ���ᱻ�ͷš�

#include <iostream>
#include <chrono>
#include <thread>

void independentThread()
{
	std::cout << "Starting concurrent thread.\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "Exiting concurrent thread.\n";
}

void threadCaller()
{
	std::cout << "Starting thread caller.\n";
	std::thread t(independentThread);
	t.detach();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Exiting thread caller.\n";
}

int main()
{
	threadCaller();
	std::cout << "main thread" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
}