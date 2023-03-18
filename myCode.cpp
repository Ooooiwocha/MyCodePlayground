#include <iostream>
#include <vector>
#include <set>
template<typename N> std::istream& operator>>(std::istream& is, std::vector<N>& obj){
    for(int i=0; i<obj.size(); i++){
        is >> obj[i];
    }
    return is;
}
template<typename N> std::ostream& operator<<(std::ostream& os, const std::vector<N>& obj){
    for(int i=0; i<obj.size(); i++){
        os << obj[i] << "\n "[i<obj.size()-1];
    }
    return os;
}
template<typename N> std::istream& operator>>(std::istream& is, std::pair<N, N>& obj){
    return is >> obj.first >> obj.second;
}
template<typename N> std::ostream& operator<<(std::ostream& os, const std::pair<N, N>& obj){
    return os << obj.first << " " << obj.second << "\n";
}
template<typename N> std::ostream& operator<<(std::ostream& os, const std::set<N>& obj){
    for(auto it=obj.begin(); it!=obj.end(); it++){
        os << *it << " \n"[it==std::prev(obj.end())];
    }
    return os;
}
int main() {
    auto v = std::vector<int>(3);
    std::cin >> v;
    auto s = std::set<int>(v.begin(), v.end());
    std::cout << std::set<int>(v.begin(), v.end()) << std::endl; //仮引数においてconst参照とされていない場合、コンパイルエラーとなる
    return 0;
}
