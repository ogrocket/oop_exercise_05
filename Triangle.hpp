#include <iostream>

template <typename T>
class Triangle{
public:
    std::pair<T, T> vertex[3];

    Triangle(){}

    Triangle(T h, T l){
        vertex[0].first = -l/2;
        vertex[0].second = 0;
        vertex[1].first = l/2;
        vertex[1].second = 0;
        vertex[2].first = 0;
        vertex[2].second = h;
    }

    T Area(){
        return vertex[2].second * vertex[1].first;
    }
};

template <class T>
std::ostream& operator << (std::ostream& cout, const Triangle<T>& t){
    cout << "(" << t.vertex[0].first << ", " << t.vertex[0].second << ")";
    cout << "(" << t.vertex[1].first << ", " << t.vertex[1].second << ")";
    cout << "(" << t.vertex[2].first << ", " << t.vertex[2].second << ")";
    cout << std::endl;
    return cout;

}





