#pragma once

namespace hThread
{
	class hDataBase
	{
		std::mutex* const pRWLock;//自锁，暂时用互斥锁代替
	protected:
		virtual bool check() const { return true; }//一般性检测
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