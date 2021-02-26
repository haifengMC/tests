#pragma once

namespace hThread
{
	class hDataBase
	{
		std::mutex rwLock;//自锁，暂时用互斥锁代替
	protected:
		virtual bool check() const { return true; }//一般性检测
		virtual void checkErrOut() const {}

	public:
		template<typename T>
		void readLk(T func);
		template<typename T>
		void writeLk(T func);

		virtual ~hDataBase() {}
	};
}