#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <memory>
/* std::pair IO */
template<typename N, typename M> std::istream& operator>>(std::istream& is, std::pair<N, M>& obj){
    return is >> obj.first >> obj.second;
}
template<typename N, typename M> std::ostream& operator<<(std::ostream& os, const std::pair<N, M>& obj){
    return os << obj.first << " " << obj.second;
}
/* std::set O */
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
/*std::map O*/
template<typename N, typename M> std::ostream& operator<<(std::ostream& os, const std::map<N, M>& obj){
    auto prev_end = std::prev(obj.end());
    for(auto it=obj.begin(); it!=obj.end(); it++){
        os << *it;
        if(it!=prev_end){
            os << " ";
        }
    }
    return os;
}
/* std::vector IO */
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
        const N start, goal, step;
        std::vector<N> *vec_ptr = nullptr;
    public:
        range(const N& start, const N& goal, const N& step): start(start), goal(goal), step(step){
            if(this->step == 0){
                throw std::runtime_error("illegal_parameter: range step must not be zero");
            }
            this->vec_ptr = new std::vector<N>(this->to_vector());
            
        }
        auto begin(){
            return vec_ptr->begin();
        }
        auto end(){
            return vec_ptr->end();
        }
        auto rbegin(){
            return vec_ptr->rbegin();
        }
        auto rend(){
            return vec_ptr->rend();
        }
        range(const N& i, const N& j): range(i, j, 1){
            
        }
        range(const N& i): range(0, i, 1){
            
        }
        std::vector<N> to_vector()const{
            if(this->vec_ptr == nullptr){
                std::vector<N> ret;
                if(0<step){
                    if(goal<=start) return ret;
                    for(N i=start; i<goal; i+=step){
                        ret.push_back(i);
                    }
                } else {
                    if(start<=goal) return ret;
                    for(N i=start; i>goal; i+=step){
                        ret.push_back(i);
                    }
                }
                return ret;
            }
            return *this->vec_ptr;
        }
        std::vector<N> to_slicer(size_t size)const{
            auto lambda = [&](N a){
                return 0 <= a? a: size + a;
            };
            return range(lambda(start), lambda(goal), step).to_vector();
        }
        virtual ~range(){
            if(vec_ptr != nullptr){
                delete this->vec_ptr;
            }
        }
};
/* slicable vector class */
template<typename N = int, class R = range<N>> class __vector: public std::vector<N>{
    public:
        using std::vector<N>::vector;
        template<class C> __vector(C& container){
            for(auto it=container.begin(); it!=container.end(); it++){
                this->push_back(*it);
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
            for(auto const &i: slice.to_slicer(this->size())){
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
template<class N>std::vector<N> operator+(std::vector<N> v1, std::vector<N>& v2){
    v1.insert(v1.end(), v2.begin(), v2.end());
    return v1;
}
/* example */
using namespace std;
int main() {
    __vector<int> vec{0, 1, 2, 3, 4, 5};
    cout << vec[-2] << " " << set(vec.begin(), vec.end()) << endl;
    print(vec[range(1, 3, 1)], "_", "(EOF)\n");
    return 0;
}
