#include <iostream>
#include <vector>

template<class N> std::istream& operator>>(std::istream& is, std::vector<N>& obj){
    for(int i=0; i<obj.size(); i++){
        is >> obj[i];
    }
    return is;
}
template<class N> std::ostream& operator<<(std::ostream& os, std::vector<N>& obj){
    for(int i=0; i<obj.size(); i++){
        os << obj[i] << "\n "[i<obj.size()-1];
    }
    return os;
}
template<class N> std::istream& operator>>(std::istream& is, std::pair<N, N>& obj){
    return is >> obj.first >> obj.second;
}
template<class N> std::ostream& operator<<(std::ostream& os, std::pair<N, N>& obj){
    return os << obj.first << " " << obj.second << "\n";
}

int main() {
    int n; std::cin >> n;
    std::vector<int> v(n);
    std::pair<int, int> p;
    std::cin >> v;
    std::cout << v;
    std::cin >> p;
    std::cout << p;
    return 0;
}
