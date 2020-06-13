struct Tst9PeterCfg { size_t idx = size_t();std::string sex = std::string();int
hight = int();float pos[2] = {}; }; template <> struct YAML::convert<Tst9PeterCf
g> { static Node encode(const Tst9PeterCfg& rhs) { NodeEx node(NodeType::Map); n
ode(IOType::PutOut); node["idx"] & rhs.idx;node["sex"] & rhs.sex;node["hight"] &
 rhs.hight;node["pos[2]"] & rhs.pos[2]; return node; } static bool decode(const
Node& node, Tst9PeterCfg& rhs) { if (!node.IsMap()) return false; NodeEx nodeEx
= node; nodeEx(IOType::PutIn); node["idx"] & rhs.idx;node["sex"] & rhs.sex;node[
"hight"] & rhs.hight;node["pos[2]"] & rhs.pos[2]; return true; } };