#include "hNodeEx.h"
#pragma once

namespace YAML
{
	inline NodeEx::NodeEx() {}

	inline NodeEx::NodeEx(const NodeType::value& type) : Node(type) {}

	template <typename T>
	NodeEx::NodeEx(const T& rhs)
	{
		Assign(rhs);
	}

	template <typename T>
	NodeEx::NodeEx(const std::initializer_list<T>& il, const EmitterStyle::value & style)
	{
		if (!IsSequence())
			reset();
		for (const T& t : il)
		{
			NodeEx node = t;
			this->push_back(node);
		}

		if (style != Style())
			SetStyle(style);
	}

	NodeEx::NodeEx(const std::initializer_list<NodeEx>& il, const NodeType::value& type)
	{
		if (!IsSequence() && !IsMap())
		{
			if (NodeType::Sequence != type && NodeType::Map != type)
				return;
			
			this->reset(Node(type));
		}

		if (IsMap())
		{
			for (const NodeEx& rhs : il)
				if (rhs.IsMap())
					for (YAML::const_iterator it = rhs.begin(); it != rhs.end(); ++it)
						this->operator[](it->first) = it->second;

			return;
		}

		for (const NodeEx& rhs : il)
		{
			if (!rhs.IsSequence())
			{
				this->push_back(rhs);
				continue;
			}

			for (YAML::const_iterator it = rhs.begin(); it != rhs.end(); ++it)
				Node::push_back(*it);
		}

	}

	template <typename T>
	NodeEx::NodeEx(const std::initializer_list<std::initializer_list<T>>& il)
	{
		if (!IsSequence())
			reset();
		for (const std::initializer_list<T>& t : il)
		{
			NodeEx node = t;
			node.SetStyle(EmitterStyle::Flow);
			this->push_back(node);
		}
	}

	template<typename K, typename T>
	inline NodeEx::NodeEx(const K& key, const T& rhs)
	{
		if (!IsMap())
			reset();
		operator[](key) = rhs;
	}

	template<typename K, typename T>
	NodeEx::NodeEx(const K& key, const std::initializer_list<T>& il, const EmitterStyle::value& style)
	{
		if (!IsMap())
			reset();
		operator[](key) = NodeEx(il, style);
	}

	template<typename K>
	NodeEx::NodeEx(const K& key, const std::initializer_list<NodeEx>& il, const NodeType::value& type)
	{
		if (!IsMap())
			reset();
		operator[](key) = NodeEx(il, type);
	}

	NodeEx::NodeEx(const Node& rhs)
	{
		AssignNode(rhs);
	}

	NodeEx::NodeEx(const NodeEx& rhs) = default;

	template <typename T>
	NodeEx& NodeEx::operator=(const T& rhs)
	{
		Assign(rhs);
		return *this;
	}

	template<typename T, size_t N>
	NodeEx& NodeEx::operator=(const T(&rhs)[N])
	{
		Node node(NodeType::Sequence);
		for (const T& element : rhs)
			node.push_back(element);
		Assign(node);
		return *this;
	}

	template<size_t N>
	NodeEx& NodeEx::operator=(const char(&rhs)[N])
	{
		Assign(rhs);
		return *this;
	}


	template<typename T, size_t N, size_t M>
	NodeEx& NodeEx::operator=(const T(&rhs)[N][M])
	{
		Node node(NodeType::Sequence);
		for (const T(&t1)[M] : rhs)
		{
			Node tnode(NodeType::Sequence);
			for (const T& t2 : t1)
				tnode.push_back(t2);
			node.push_back(tnode);
		}
		Assign(node);
		return *this;
	}

	NodeEx& NodeEx::operator=(const Node& rhs)
	{
		AssignNode(rhs);
		return *this;
	}

	NodeEx& NodeEx::operator()(const std::string& tag)
	{
		SetTag(tag);
		return *this;
	}

	NodeEx& NodeEx::operator()(const EmitterStyle::value& style)
	{
		if (!IsSequence() && !IsMap())
			return *this;

		for (iterator it = begin(); it != end(); ++it)
		{
			const NodeType::value& type = IsSequence() ? it->Type() : it->second.Type();
			Node node = IsSequence() ? *it : it->second;
			node.SetStyle(style);
		}
		return *this;
	}

	NodeEx& NodeEx::operator()(const IOType::value& io)
	{
		m_io = io;
		return *this;
	}

	template <typename T>
	NodeEx& NodeEx::operator&(T& rhs)
	{
		switch (m_io)
		{
		case IOType::PutIn:
			rhs = as<T>();
			break;
		case IOType::PutOut:
			operator=(rhs);
			break;
		default:
			break;
		}
		return *this;
	}

	template <typename T>
	NodeEx& NodeEx::operator&(const T& rhs)
	{
		if (YAML::IOType::PutIn == m_io)
			return *this;
	
		operator=(rhs);
		return *this;
	}

	template<typename T, size_t N>
	NodeEx& NodeEx::operator&(T(&rhs)[N])
	{
		switch (m_io)
		{
		case YAML::IOType::PutIn:
			{
				if (!IsSequence())
					break;
				size_t count = 0;
				for (iterator it = begin(); it != end() && count < N; ++it, ++count)
					if (it->IsScalar()) 
						rhs[count] = it->as<T>();
			}
			break;
		case YAML::IOType::PutOut:
			operator=(rhs);
			break;
		default:
			break;
		}
		return *this;
	}

	template<typename T, size_t N>
	NodeEx& NodeEx::operator&(const T(&rhs)[N])
	{
		if (YAML::IOType::PutIn == m_io)
			return *this;

		operator=(rhs);
		return *this;
	}


	template<typename T, size_t N, size_t M>
	NodeEx& NodeEx::operator&(T(&rhs)[N][M])
	{
		switch (m_io)
		{
		case YAML::IOType::PutIn:
			{
				if (!IsSequence())
					break;
				size_t nCnt = 0;
				for (Node::const_iterator it1 = begin(); it1 != end() && nCnt < N; ++it1, ++nCnt)
				{
					T(&t1)[M] = rhs[nCnt];
					if (!it1->IsSequence())
						continue;
					size_t mCnt = 0;
					for (Node::const_iterator it2 = it1->begin(); it2 != it1->end() && mCnt < M; ++it2, ++mCnt)
						if (it2->IsScalar()) 
							t1[mCnt] = it2->as<T>();
				}
			}
			break;
		case YAML::IOType::PutOut:
			operator=(rhs);
			break;
		default:
			break;
		}
		return *this;
	}


	template<typename T, size_t N, size_t M>
	NodeEx& NodeEx::operator&(const T(&rhs)[N][M])
	{
		if (YAML::IOType::PutIn == m_io)
			return *this;

		operator=(rhs);
		return *this;
	}

	void NodeEx::push_back(const NodeEx& rhs)
	{
		const Node& node = rhs;
		Node::push_back(node);
	}

	template <typename Key>
	inline const NodeEx NodeEx::operator[](const Key& key) const
	{ 
		NodeEx node = Node::operator[](key);
		return node(m_io);
	}

	template <typename Key>
	inline NodeEx NodeEx::operator[](const Key& key)
	{ 
		NodeEx node = Node::operator[](key);
		return node(m_io);
	}

	bool operator<<(std::string fileName, const NodeEx& node)
	{
		std::ofstream fout(fileName);
		if (!fout) return false;
		fout << node;
		fout.close();
		return true;
	}

	bool operator>>(std::string fileName, NodeEx& node)
	{
		std::ifstream fin(fileName);
		if (!fin) return false;
		try
		{
			node = Load(fin);
			fin.close();
		}
		catch (const ParserException&)
		{
			fin.close();
			return false;
		}
		return true;
	}
}