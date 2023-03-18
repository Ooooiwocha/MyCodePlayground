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
template<typename N, typename M> std::ostream& operator<<(std::ostream& os, const std::pair<N, M>& obj){
    return os << obj.first << " " << obj.second;
}
template<typename N> std::ostream& operator<<(std::ostream& os, const std::set<N>& obj){
    for(auto it=obj.begin(); it!=obj.end(); it++){
        os << *it;
        if(it!=std::prev(obj.end())){
            os << " ";
        }
    }
    return os;
}
template<typename N> class range{
    private:
        const N start, end, step;
    public:
        range(const N& start, const N& end, const N& step): start(start), end(end), step(step){
            
        }
        range(const N& i, const N& j): range(i, j, 1){
            
        }
        range(const N& i): range(0, i, 1){
            
        }
    std::vector<N> to_vector()const{
        std::vector<N> ret;
        for(int i=start; i<end; i+=step){
            ret.push_back(i);
        }
        return ret;
    }
    
};
template<typename N, typename M> std::vector<N> operator&&(std::vector<N> v, range<M> r){
    std::vector<N> ret;
    for(auto &i: r.to_vector()){
        ret.push_back(v.at(i));
    }
    return ret;
}
int main() {
    /*
    auto v = std::vector<int>(3);
    std::cin >> v;
    auto s = std::set<int>(v.begin(), v.end());
    auto r = v && range(0, 3, 2);
    std::cout << std::set<int>(v.begin(), v.end()) << std::endl; //仮引数においてconst参照とされていない場合、コンパイルエラーとなる
    std::cout << r << std::endl;
    */
    return 0;
}
