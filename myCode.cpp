#include <iostream>
#include <vector>
#include <set>
/* pair IO */
template<typename N, typename M> std::istream& operator>>(std::istream& is, std::pair<N, M>& obj){
    return is >> obj.first >> obj.second;
}
template<typename N, typename M> std::ostream& operator<<(std::ostream& os, const std::pair<N, M>& obj){
    return os << obj.first << " " << obj.second;
}
/* set O */
template<typename N> std::ostream& operator<<(std::ostream& os, const std::set<N>& obj){
    auto prev_end = std::prev(obj.end());
    for(auto it=obj.begin(); it!=obj.end(); it++){
        os << *it;
        if(it!=prev_end){
            os << " ";
        }
    }
    return os;
}
/* vector IO */
template<typename N> std::istream& operator>>(std::istream& is, std::vector<N>& obj){
    for(auto it=obj.begin(); it!=obj.end(); it++){
        is >> *it;
    }
    return is;
}
template<typename N> std::ostream& operator<<(std::ostream& os, const std::vector<N>& obj){
    for(auto it=obj.begin(); it!=obj.end(); it++){
        os << *it;
        if (it!=std::prev(obj.end())){
            os << " ";
        }
    }
    return os;
}
/* Python-like range class */
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
            if(0<step){
                for(N i=start; i<end; i+=step){
                    ret.push_back(i);
                }
            } else {
                for(N i=start; i>end; i+=step){
                    ret.push_back(i);
                }
            }
            return ret;
        }
};
/* slicable vector class */
template<typename N = int, class R = range<N>> class __vector: public std::vector<N>{
    public:
        using std::vector<N>::vector;
        explicit __vector(std::vector<N>& v){
            for(auto it=v.begin(); it!=v.end(); it++){
                this->push.back(*it);
            }
        }
        N at(long long int index){
            long long int __index = 0<=index? index: this->size() + index;
            return this->std::vector<N>::at(__index);
        }
        N operator[](long long int index){
            long long int __index = 0<=index? index: this->size() + index; 
            return this->at(__index);
        }
        __vector<N> operator[](R slice){ //Python-like slicing
            __vector<N> ret;
            for(auto const &i: slice.to_vector()){
                ret.push_back(this->at(i));
            }
            return ret;
        }
};
/* Python-like print function */
template<class N> void print(N container, std::string sep=" ", std::string end="\n"){ 
    auto prev_end = prev(container.end());
    for(auto it=container.begin(); it!=container.end(); it++){
        std::cout << *it;
        if(it!=prev_end){
            std::cout << sep;
        }
    }
    std::cout << end;
}
using namespace std;
int main() {
    __vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << vec << std::endl;
    std::cout << vec[range(-8, 2, 1)] << std::endl;
    std::cout << vec[-8] << std::endl;
    int n; std::cin >> n;
    __vector<int> v(n);
    std::cin >> v;
    std::cout << v << std::endl;
    std::cout << v << std::endl; 
    print(std::string("aaa"), "_", "(EOF)\n");
    return 0;
}
