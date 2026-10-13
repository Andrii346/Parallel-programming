#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <chrono>

//void Thread1() {
//    std::cout << 1 << std::endl;
//}
//
//void Thread2() {
//    std::cout << 2 << std::endl;
//}
//
//int main() {
//    std::thread t1(Thread1);
//    std::thread t2(Thread2);   
//    return 0;
//}

////ex2
//
//void Thread1() {
//    std::cout << 1 << std::endl;
//}
//
//void Thread2() {
//    std::cout << 2 << std::endl;
//}
//
//int main() {
//    std::thread t1(Thread1);
//    std::thread t2(Thread2);
//    t1.detach();
//    t2.detach();
//    return 0;
//}
////ex3
//std::vector<int> l;
//
//void AddToList(int startVal) {
//    for (int i = 0; i < 10; ++i) {
//        l.push_back(startVal + i);
//        std::cout << "[AddToList] Додано: " << (startVal + i) << "\n";
//        std::this_thread::sleep_for(std::chrono::milliseconds(2));
//    }
//}
//
//void ListContains(int targetVal) {
//    for (int i = 0; i < 10; ++i) {
//        bool found = (std::find(l.begin(), l.end(), targetVal) != l.end());
//        std::cout << "[ListContains] Спроба " << (i + 1) << ": "
//            << (found ? "входить" : "не входить") << "\n";
//        std::this_thread::sleep_for(std::chrono::milliseconds(2));
//    }
//}
//
//int main() {
//    int startVal = 100;
//    std::thread t1(AddToList, startVal);
//    std::thread t2(ListContains, startVal);
//
//    t1.join();
//    t2.join();
//
//    return 0;
//}
////ex4

//std::vector<int> l;
//std::mutex mtx;
//
//void AddToList(int startVal) {
//    for (int i = 0; i < 10; ++i) {
//        mtx.lock();
//        l.push_back(startVal + i);
//        std::cout << "[AddToList] Додано: " << (startVal + i) << "\n";
//        mtx.unlock();
//        std::this_thread::sleep_for(std::chrono::milliseconds(2));
//    }
//}
//
//void ListContains(int targetVal) {
//    for (int i = 0; i < 10; ++i) {
//        mtx.lock();
//        bool found = (std::find(l.begin(), l.end(), targetVal) != l.end());
//        std::cout << "[ListContains] Спроба " << (i + 1) << ": "
//            << (found ? "входить" : "не входить") << "\n";
//        mtx.unlock();
//        std::this_thread::sleep_for(std::chrono::milliseconds(2));
//    }
//}
//
//int main() {
//    int startVal = 100;
//    std::thread t1(AddToList, startVal);
//    std::thread t2(ListContains, startVal);
//
//    t1.join();
//    t2.join();
//
//    return 0;
//}
////ex5

//std::vector<int> l;
//std::mutex mtx;
//
//void AddToList(int val) {
//    std::lock_guard<std::mutex> lock(mtx);
//    l.push_back(val);
//    std::cout << "[AddToList] Додано: " << val << "\n";
//}
//
//void ListContains(int targetVal, int attempt) {
//    std::lock_guard<std::mutex> lock(mtx);
//    bool found = (std::find(l.begin(), l.end(), targetVal) != l.end());
//    std::cout << "[ListContains] Спроба " << attempt << ": "
//        << (found ? "входить" : "не входить") << "\n";
//}
//
//int main() {
//    int baseVal = 100;
//
//    for (int i = 0; i < 10; ++i) {
//        std::thread tAdd(AddToList, baseVal + i);
//        tAdd.detach();
//
//        std::thread tCheck(ListContains, baseVal, i + 1);
//        tCheck.detach();
//    }    
//    std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    return 0;
//}

////ex6

//struct someData {
//    std::string firstName;
//    std::string lastName;
//    std::string address;
//    int age = 0;
//};
//
//class exchangePerson {
//public:
//    someData data;
//    std::mutex mtx;
//
//    static void JohnDoe(exchangePerson& p) {
//        std::lock_guard<std::mutex> lock(p.mtx);
//        p.data.firstName = "John";
//        p.data.lastName = "Doe";
//        p.data.address = "Unknown";
//        p.data.age = 120;
//    }
//
//    static void JacobSmith(exchangePerson& p) {
//        std::lock_guard<std::mutex> lock(p.mtx);
//        p.data.firstName = "Jacob";
//        p.data.lastName = "Smith";
//        p.data.address = "Known";
//        p.data.age = 1;
//    }
//
//    static void Swap(exchangePerson& p1, exchangePerson& p2) {        
//        if (&p1 == &p2) return;        
//        std::lock(p1.mtx, p2.mtx);        
//        std::lock_guard<std::mutex> lock1(p1.mtx, std::adopt_lock);
//        std::lock_guard<std::mutex> lock2(p2.mtx, std::adopt_lock);
//
//        std::cout << "--- До обміну ---\n";
//        std::cout << "P1: " << p1.data.firstName << " " << p1.data.lastName << ", "
//            << p1.data.address << ", " << p1.data.age << "\n";
//        std::cout << "P2: " << p2.data.firstName << " " << p2.data.lastName << ", "
//            << p2.data.address << ", " << p2.data.age << "\n";
//        std::swap(p1.data, p2.data);
//        std::cout << "--- Після обміну ---\n";
//        std::cout << "P1: " << p1.data.firstName << " " << p1.data.lastName << ", "
//            << p1.data.address << ", " << p1.data.age << "\n";
//        std::cout << "P2: " << p2.data.firstName << " " << p2.data.lastName << ", "
//            << p2.data.address << ", " << p2.data.age << "\n";
//    }
//};
//
//int main() {
//    exchangePerson p1;
//    exchangePerson p2;
//    std::thread t1(exchangePerson::JohnDoe, std::ref(p1));
//    std::thread t2(exchangePerson::JacobSmith, std::ref(p2));
//    t1.detach();
//    t2.detach();    
//    std::this_thread::sleep_for(std::chrono::milliseconds(10));    
//    std::thread tSwap(exchangePerson::Swap, std::ref(p1), std::ref(p2));
//    tSwap.join();
//    return 0;
//}


//ex7

struct someData {
    std::string firstName;
    std::string lastName;
    std::string address;
    int age = 0;
};

class exchangePerson {
public:
    someData data;
    std::mutex mtx;

    static void JohnDoe(exchangePerson& p) {
        std::lock_guard<std::mutex> lock(p.mtx);
        p.data.firstName = "John";
        p.data.lastName = "Doe";
        p.data.address = "Unknown";
        p.data.age = 120;
    }

    static void JacobSmith(exchangePerson& p) {
        std::lock_guard<std::mutex> lock(p.mtx);
        p.data.firstName = "Jacob";
        p.data.lastName = "Smith";
        p.data.address = "Known";
        p.data.age = 1;
    }

    static void Swap(exchangePerson& p1, exchangePerson& p2) {
        if (&p1 == &p2) return;        
        std::unique_lock<std::mutex> lock1(p1.mtx, std::defer_lock);
        std::unique_lock<std::mutex> lock2(p2.mtx, std::defer_lock);        
        std::lock(lock1, lock2);

        std::cout << "--- До обміну (unique_lock) ---\n";
        std::cout << "P1: " << p1.data.firstName << " " << p1.data.lastName << ", "
            << p1.data.address << ", " << p1.data.age << "\n";
        std::cout << "P2: " << p2.data.firstName << " " << p2.data.lastName << ", "
            << p2.data.address << ", " << p2.data.age << "\n";

        std::swap(p1.data, p2.data);

        std::cout << "--- Після обміну (unique_lock) ---\n";
        std::cout << "P1: " << p1.data.firstName << " " << p1.data.lastName << ", "
            << p1.data.address << ", " << p1.data.age << "\n";
        std::cout << "P2: " << p2.data.firstName << " " << p2.data.lastName << ", "
            << p2.data.address << ", " << p2.data.age << "\n";
    }
};

int main() {
    exchangePerson p1;
    exchangePerson p2;
    std::thread t1(exchangePerson::JohnDoe, std::ref(p1));
    std::thread t2(exchangePerson::JacobSmith, std::ref(p2));
    t1.detach();
    t2.detach();   
    std::this_thread::sleep_for(std::chrono::milliseconds(10));    
    std::thread tSwap(exchangePerson::Swap, std::ref(p1), std::ref(p2));
    tSwap.join();

    return 0;
}
