#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <thread>
using namespace std;

/*    Language Runtime Enhancements    */

/*
    - A lambda is essentially a function without a name that you can define directly where you need it.
    - A lambda lets you create a small callable piece of code locally, without defining a separate named function.

    Lambda Syntax:
    [capture list] (parameter list) mutable(optional) exception(optional) attribute(optional) -> return type {
        // function body
    }

    Example:
    [&x] (int a) mutable noexcept -> int {
        return x + a;
    }
*/

// The most common lambda you'll see is simply:
auto res = [](int x) {
    return x * 2;
};


/*
    15. Why is noexcept useful?

    - It can allow the compiler/library to make stronger assumptions.
    - It's particularly important with things such as:
        std::vector
      and move operations.

    For example, standard containers can sometimes prefer moving an object only when its move constructor is noexcept, 
    because moving isn't expected to throw.
    For ordinary lambdas, though, 
    you don't need to add noexcept unless you have a reason to guarantee non-throwing behavior.
*/


/*
    15. attribute
    Attributes are metadata/instructions that tell the compiler something about a declaration or expression.

    Syntax: [[attribute]]

    For example:
*/
[[nodiscard]]  // means: "The caller should not ignore this return value."
int calculate() {
    return 42;
}
// calculate();  // warning: ignoring return value of function declared with 'nodiscard' attribute
int result = calculate();  // but this is fine, bacuase we are using it

/*
    Why [[attribute]] are useful?
    
    1. For functions where ignoring the result is probably a bug:
*/
[[nodiscard]]
bool saveFile();  // Did you forget to check whether it succeeded?

/*
    Attributes aren't lambda-specific

    Things like:
        [[deprecated]]
        [[nodiscard]]
        [[maybe_unused]]
    are part of the broader C++ attribute system.
*/


/***     Lambda: Main Use Cases      ***/

// Use-Case #1 — STL algorithms
// Bad example:
bool isGreater(int a, int b) {
    return a > b;
}


/*      Use-Case #2 — Callbacks     */
// Suppose some function needs code that it should execute later.
// Ex-1:
void execute(std::function<void()> callback) {
    callback();
}
/*
    What does std::function<void()> mean?

    means: "A variable that can hold anything callable that takes no arguments and returns void."
*/

// Ex-2:
void downloadFile(function<void()> onFinished){
    // donload logic ...
    onFinished();
}

/*
    ----->  A lambda is actually an object  <-----
    When you write:
    auto lambda = [x](int y) {
        return x + y;
    };
    
    C++ essentially creates a unique unnamed class type behind the scenes.
    Conceptually, something like:

    class SomeCompilerGeneratedType {
        private:
            int x;
        public:
            SomeCompilerGeneratedType(int x) : x(x)
            { 
            }

            int operator()(int y)
            {
                return x + y;
            }
    };

    Then:
        lambda(5);

    is conceptually:
        lambade.operator()(5);

    This explains why lambdas can capture state.
    The captured variables are essentially stored inside the lambda object.

    This is why I recommend thinking: 
    Lambda = small object + operator()
*/


int main() {

    /*      Use-Case #1 — STL algorithms     */
    vector<int> v = {4, 3, 8, 5, 0, 1, 2, 9};

    std::sort(v.begin(), v.end(), isGreater);
    // But what if this comparison is needed only once?
    // Creating a named function somewhere else is unnecessary.

    // With a lambda:
    std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    // Lambdas allow you to define behavior locally, exactly where it is needed.

    // Another Example:
    std::for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
    cout << endl;

    // Another Example:
    auto it = std::find_if(v.begin(), v.end(), [](int x) { return x > 5; });

    if (it != v.end())
        cout << "Found " << *it << " at index " << std::distance(v.begin(), it) << endl;
    
    
    /*      Use-Case #2 — Callbacks     */

    // Ex-1:
    execute([]() {
        cout << "Done!" << endl; 
    });
    /*
        The lambda is acting as a callback.

        This is extremely common in:
            GUI programming
            event systems
            asynchronous programming
            networking
            timers
            task systems
    */

    // Ex-2:
    downloadFile([]() {
        cout << "Download complete!\n";
    });
    

    /*      Use-Case #3 — Capturing Local State     */
    vector<int> numbers = {4, 3, 8, 5, 0, 1, 2, 9};
    int limit = 5;

    auto greaterThanLimit = [limit](int x) {
        return x > limit;
    };

    it = std::find_if(numbers.begin(), numbers.end(), greaterThanLimit);
    // A normal free function would need the limit passed explicitly.
    // The lambda can carry state with it.
    // That's one of its biggest advantages.

    if (it != numbers.end())
        cout << std::distance(numbers.begin(), it) << endl;

    
    /*      Use-Case #4 — Threads     */
    int z = 10;

    thread t1([z]() {
        cout << "z: " << z << endl;
    });

    t1.join();   // Lambda provides the code that new thread should execute

    // Ex-2: We can also capyure the date
    string name = "Rustam";

    thread t2([name]() {
        cout << "Thread t2 executed by name: " << name << endl;
    });
    t2.join();


    /*      Use-Case #5 — Tiny Local Operations     */
    auto powerOfTwo = [](int x) {
        return x * x;
    };
    // If it's only needed in one small section of code, a lambda can be cleaner than creating a global/named function.

    cout << "power of 2 of 5: " << powerOfTwo(5) << endl;


    /*   Complete Syntax Example    */
    int k = 10;

    auto lamb =
        [k]
        (int y)
        mutable
        noexcept
        -> int
    {
        // capture by value/refrence
        // parameters
        // can change captured value
        // exception specification
        // return type
        return k + y;
    };


    // 1. [capture list] => Which variables from the surrounding scope the lambda can use.
    int multiplier = 10;
    auto multiply = [multiplier](int x) {
        return x * multiplier;
    };

    cout << multiply(5) << endl;
    /*
        int multiplier = 10;
        auto multiply = [](int x)
        {
            return x * multiplier; // ❌
        };

        This doesn't work because the lambda doesn't automatically have access to local variables.
    */


    int x = 10;

    // 2. Capture By Value: The lambda gets its own copy of x.
    auto lambda1 = [x]() {
        cout << x << endl;
    };

    x = 100;
    lambda1();  // 10


    // 3. Capture By Reference: Now the lambda refers to the original x.
    auto lambda2 = [&x]() {
        x++;
    };

    lambda2();
    cout << x << endl;  // 101


    int a = 10;
    int b = 20;

    // 4. Capture Everything: [=]
    auto lambda3 = [=]() {
        return a + b;  // Both are captured by value.
    };

    cout << lambda3() << endl;  // 30


    // 5. Capture Everything By Reference: [&]
    auto lambda4 = [&]() {
        a++;
        b++;
    };

    lambda4();
    cout << a << " " << b << endl;  // 11 21


    // 6. We can mix them: [=, &var]
    auto lambda5 = [=, &b]() {
        // [multiplier, x, a] -> captured by value
        // b -> captured by reference
    };

    auto lambda6 = [&, a]() {
        // everything else captured by reference
        // a -> captured by value
    };


    // 7. [this] capture
    class Person {
        int age = 25;

    public:
        void print() {
            auto lambda = [this]() {
                cout << this->age << endl;
            };

            lambda();
        }

        void display() {
            // 8. [*this] - captures the copy of the current object.
            // Modern C++ also has: auto lambda = [*this]() mutable { (*this).print(); };
        }
    };

    Person person;
    person.print();


    // 9. Parameter List: 
    // This part works almost exactly like a normal function
    auto add = [](int a, int b) {
        return a + b;
    };

    // We can omit parameters by ()
    auto hello = []() {
        cout << "Hello" << endl;
    };

    // We can even omit the ():
    auto sayHello = [] {
        cout << "Hello" << endl;
    };


    // 10. Mutable: This is specifically related to value captures
    auto lambda7 = [x]() {
        // x++; // ❌   Why?
        // Because the lambda's captured-by-value x is treated as non-modifiable inside a normal lambda.
    };

    // Add mutable:
    x = 10;
    auto lambda8 = [x]() mutable {
        x++;
        cout << x << endl;  // 11
    };

    lambda8();
    // Important: inside the lambda is still the lambda's copy.


    // 11. mutable does NOT mean modifying the original
    x = 10;
    auto lambda9 = [x]() mutable {
        x = 100;
    };
    cout << x << endl;  // 10


    // 12. -> return type
    // normally C++ can automatically determine the return type:
    auto add1 = [](int a, int b) {
        return a + b;
    };

    // explicitly specify: 
    auto add2 = [](int a, int b) -> int {
        return a + b;
    };


    // 13. When is explicit return type useful?

    // Mostly when the return type isn't obvious or you want to force it.
    auto div = [](int x) -> double {
        return x / 2.0;
    };

    // Or when different branches new a specifc retrun type
    auto conditional = [](bool condition) -> double {
        if (condition)
            return 10;
        return 10.5;
    };


    // 14. noexcept means: this function promises not to throw exceptions:
    auto square = [](int x) noexcept {
        return x * x;
    };
    // If an exception somehow escapes a noexcept function, the program calls:
    // std::terminate();

    // So don't use noexcept merely because you don't expect an exception.
    cout << 45 << endl;


    // 15. attribute
    // warning: ignoring return value of function declared with 'nodiscard' attribute
    calculate();

    return 0;
}