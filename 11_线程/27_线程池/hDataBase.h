#pragma once

namespace hThread
{
	class hDataBase
	{
		std::mutex* const pRWLock;//��������ʱ�û���������
	protected:
		virtual bool check() const { return true; }//һ���Լ��
		virtual void checkErrOut() const {}

	public:
		template<typename T>
		void readLk(T func);
		template<typename T>
		void readLk(T func) const;
		template<typename T>
		void writeLk(T func);
		template<typename T>
		void writeLk(T func) const;

		hDataBase() : pRWLock(new std::mutex) {}
		virtual ~hDataBase() { delete pRWLock; }
	};
}