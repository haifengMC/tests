#pragma once

namespace YAML
{
	class NodeEx : public Node
	{
	public:
		NodeEx();
		template <typename T>
		NodeEx(const T& rhs);
		template <typename T>
		NodeEx(const std::initializer_list<T>& il, const EmitterStyle::value& = EmitterStyle::Default);
		NodeEx(const std::initializer_list<NodeEx>& il, const NodeType::value& type = NodeType::Map);
		template<typename T>
		NodeEx(const std::initializer_list<std::initializer_list<T>>& il);
		template<typename K, typename T>
		NodeEx(const K& key, const T& rhs); 
		template<typename K, typename T>
		NodeEx(const K& key, const std::initializer_list<T>& il, const EmitterStyle::value & = EmitterStyle::Default);
		template<typename K>
		NodeEx(const K& key, const std::initializer_list<NodeEx>& il, const NodeType::value& type = NodeType::Map);
		NodeEx(const Node& rhs);
		NodeEx(const NodeEx& rhs);

		template <typename T>
		NodeEx& operator=(const T& rhs);
		template<typename T, size_t N>
		NodeEx& operator=(const T(&rhs)[N]);
		template<size_t N>
		NodeEx& operator=(const char(&rhs)[N]);
		NodeEx& operator=(const Node& rhs);

		NodeEx& operator()(const std::string& tag);
		NodeEx& operator()(const const EmitterStyle::value& style);

		//sequence
		void push_back(const NodeEx& rhs);

		template <typename Key>
		const NodeEx operator[](const Key& key) const;
		template <typename Key>
		NodeEx operator[](const Key& key);

		friend bool operator<<(std::string fileName, const NodeEx& node);
		friend bool operator>>(std::string fileName, NodeEx& node);

	};
}