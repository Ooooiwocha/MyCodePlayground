#include <iostream>
#include <vector>
#include <set>
template<typename N, typename M> std::istream& operator>>(std::istream& is, std::pair<N, M>& obj){
    return is >> obj.first >> obj.second;
}
template<typename N, typename M> std::ostream& operator<<(std::ostream& os, const std::pair<N, M>& obj){
    return os << obj.first << " " << obj.second;
}
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

template<typename N> std::istream& operator>>(std::istream& is, std::vector<N>& obj){
    for(int i=0; i<obj.size(); i++){
        is >> obj[i];
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
        __vector<N> operator[](R slice){
            __vector<N> ret;
            for(auto const &i: slice.to_vector()){
                ret.push_back(this->at(i));
            }
            return ret;
        }
};

int main() {
    __vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << vec << std::endl;
    std::cout << vec[range(-8, 2, 1)] << std::endl;
    std::cout << vec[-8] << std::endl;
    return 0;
}
