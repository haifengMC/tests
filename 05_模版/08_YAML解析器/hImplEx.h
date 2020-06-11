#include "hNodeEx.h"
#pragma once

namespace YAML
{
	inline NodeEx::NodeEx() {}

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
		if (!IsSequence())
			reset();
		for (const T& element : rhs)
			this->push_back(element);
		return *this;
	}

	template<size_t N>
	NodeEx& NodeEx::operator=(const char(&rhs)[N])
	{
		Assign(rhs);
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
	NodeEx& NodeEx::operator()(const const EmitterStyle::value& style)
	{
		SetStyle(style);
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
		return Node::operator[](key); 
	}

	template <typename Key>
	inline NodeEx NodeEx::operator[](const Key& key)
	{ 
		return Node::operator[](key); 
	}

	bool operator<<(std::string fileName, const NodeEx& node)
	{
		std::ofstream fout(fileName);
		if (!fout) return false;
		fout << node;
		return true;
	}

	bool operator>>(std::string fileName, NodeEx& node)
	{
		std::ifstream fin(fileName);
		if (!fin) return false;
		try
		{
			node = Load(fin);
		}
		catch (const ParserException&)
		{
			return false;
		}

		return true;
	}
}