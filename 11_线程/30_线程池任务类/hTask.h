#pragma once


class Task;

//��������(��̬����)
struct TaskAttr
{
	bool loop = false;//�Ƿ���ѭ������

	size_t weight = 0;//Ȩ��
	size_t thrdExpect = 0;//�ڴ��߳���


	~TaskAttr() {}//��Ҫʵ������
};
//����״̬(����ʱ����)
struct TaskStat
{
	size_t state = 0;//��ǰ״̬
	std::list<Task*>::iterator stateIt;//ָ��ǰ״̬�ĵ�����

	void* pMgr = NULL;//ָ���Լ����ڹ�����

	~TaskStat() {}//��Ҫʵ������
};

class Task : public hTool::hUniqueMapVal<size_t, Task>
{
	size_t thisId = 0;//����Ψһid

	hTool::hAutoPtr<TaskAttr> attr;
	hTool::hAutoPtr<TaskStat> stat;
public:
	Task(hTool::hAutoPtr<TaskAttr> attr);
	Task(Task&& t);
private:
};
