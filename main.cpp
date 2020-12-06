#include <iostream>
#include <algorithm>
#include "Queue.hpp"
#include "Triangle.hpp"

void menu();

int main(){
    Queue<Triangle<int>> queue;
    auto Print = [](Node<Triangle<int>> T){ std::cout << T << std::endl; };
    menu();

    int variant;
    int l, h, index;

    do {
        std::cin >> variant;
        switch (variant) {
            case 1:{
                std::cout << "Enter the base of the triangle: " << std::endl;
                std::cin >> l;
                std::cout << "Enter the height of the triangle: " << std::endl;
                std::cin >> h;
                Triangle<int> T(h ,l);
                std::cout << "Triangle successfully added\n";
                queue.Push(T);
                break;
            }

            case 2:{
                std::cout << "Enter the base of the triangle: " << std::endl;
                std::cin >> l;
                std::cout << "Enter the height of the triangle: " << std::endl;
                std::cin >> h;
                Triangle<int> T(h ,l);
                std::cout << "Enter the index: " << std::endl;
                std::cin >> index;
                try {
                    if (queue.Size() - 1 < index) {
                        throw std::invalid_argument("Entered the wrong index!\n");
                    }
                    else {
                        auto iterator = queue.Begin();
                        while (--index){
                            ++iterator;                        }
                        queue.Insert(iterator, T);
                        std::cout << "Triangle successfully added\n";
                    }
                }
                catch(int){
                    std::cout << "Out of range\n" << std::endl;
                }
                break;
            }

            case 3:{
                queue.Pop();
                std::cout << "Triangle successfully deleted\n";
            }

            case 4:{
                std::cout << "Enter the index: " << std::endl;
                std::cin >> index;
                try{
                    auto iterator = queue.Begin();
                    while (--index){
                        ++iterator;
                    }
                    queue.Erase(iterator);
                    std::cout << std::endl << "Triangle successfully deleted" << std::endl;
                }
                catch(int){
                    std::cout << std::endl << "Out of range" << std::endl;
                }
                break;
            }

            case 5:{
                try
                {
                    if(queue.Begin().Null())
                        throw -1;
                    std::for_each(queue.Begin(),queue.End(),Print);
                }
                catch(int)
                {
                    std::cout << std::endl << "Queue is empty" << std::endl;
                }
                break;
            }
            case 6:{
                double minimal_area;
                std::cout << "Enter the minimal area: ";
                std::cin >> minimal_area;
                auto triangles_less_area = [&minimal_area](Node<Triangle<int>> &t) {
                    return t.data.Area() < minimal_area;
                };
                std::cout << "Triangles with area less than the specified: " <<
                        std::count_if(queue.Begin(), queue.End(), triangles_less_area) << "\n";
                break;
            }
        }
    } while (variant != 0);
    return 0;
}



void menu() {
    std::cout << "0. Exit\n";
    std::cout << "1. Add triangle as queue\n";
    std::cout << "2. Add triangle by index\n";
    std::cout << "3. Delete triangle as from queue\n";
    std::cout << "4. Delete triangle by index\n";
    std::cout << "5. Print triangles from the collection\n";
    std::cout << "6. Print the number of triangles whose area is less than the specified\n";
}
