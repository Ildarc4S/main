#include <iostream>
#include <string>

namespace n82
{
    class MyClass
    {
    public:
        int* data;
        
        MyClass(int size)
        {
            this->Size = size;
            this->data = new int[size];
            for (int i = 0; i < size; i++)
            {
                data[i] = i;
            }

        }

        MyClass(const MyClass& other)
        {
            this->Size = other.Size;

            this->data = new int[other.Size];
            for (int i = 0; i < other.Size; i++)
            {
                this->data[i] = other.data[i];
            }

        }

        ~MyClass()
        {
            delete[] data;
        }

    private:
        int Size;
    };
}

namespace n83
{
    class MyClass
    {
    public:
        int* data;

        MyClass(int size)
        {
            this->Size = size;
            this->data = new int[size];
            for (int i = 0; i < size; i++)
            {
                data[i] = i;
            }

        }

        MyClass(const MyClass& other)
        {
            this->Size = other.Size;

            this->data = new int[other.Size];
            for (int i = 0; i < other.Size; i++)
            {
                this->data[i] = other.data[i];
            }

        }

        MyClass& operator=(const MyClass &other)
        {
         
            this->Size = other.Size;

            if (this->data != nullptr)
            {
                delete[] this->data;
            }

            this->data = new int[other.Size];

            for (int i = 0; i < other.Size; i++)
            {
                this->data[i] = other.data[i];
            }

            return *this;
        }

        ~MyClass()
        {
            delete[] data;
        }

    private:
        int Size;
    };
}

namespace n84
{
    class Point
    {
    public:
        Point(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

        void Get()
        {
            std::cout << this->x << " " << this->y << std::endl;
        }

        bool operator==(const Point &other)
        {
            return this->x == other.x && this->y == other.y;
        }
        
        bool operator!=(const Point& other)
        {
            return !(this->x == other.x && this->y == other.y);
        }


    private:
        int x;
        int y;
    };
}

namespace n86
{
    /*
    * лооох
        n86::Point a(2, 3);
        a++;
        ++a;
        --a;
        a--;
    */

    class Point

    {
    public:
        Point()
        {

        }

        Point(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

        void Get()
        {
            std::cout << this->x << " " << this->y << std::endl;
        }

        bool operator ==(const Point& other)
        {
            return this->x == other.x && this->y == other.y;
        }

        bool operator !=(const Point& other)
        {
            return !(this->x == other.x && this->y == other.y);
        }

        Point operator +(const Point& other)
        {
            Point temp;
            temp.x = this->x + other.x;
            temp.y = this->y + other.y;
            
            return temp;
        }

        Point& operator ++()
        {
            this->x++;
            this->y++;
            return * this;
        }

        Point& operator ++(int value)
        {
            Point temp(*this);

            this->x++;
            this->y++;
            
            return temp;
        }

        Point& operator --()
        {
            this->x--;
            this->y--;
            return *this;
        }

        Point& operator --(int value)
        {
            Point temp(*this);

            this->x--;
            this->y--;

            return temp;
        }

    private:
        int x;
        int y;
    };
}

namespace n87
{
    /*
            n87::TestClass a;

            int b = a[0];
    */

    class TestClass
    {
    public:
        int& operator[] (int index)
        {
            return arr[index];
        }

    private:
        int arr[5]{ 23,34,7,64,20 };
    };

}

namespace n88
{
    /*
        дружественные функции
    */

    class Point
    {
    public:
        Point(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

        Point();

        void Get()
        {
            std::cout << this->x << " " << this->y << std::endl;
        }

        bool operator ==(const Point& other)
        {
            return this->x == other.x && this->y == other.y;
        }

        bool operator !=(const Point& other)
        {
            return !(this->x == other.x && this->y == other.y);
        }

        Point operator +(const Point& other)
        {
            Point temp;
            temp.x = this->x + other.x;
            temp.y = this->y + other.y;

            return temp;
        }

        Point& operator ++()
        {
            this->x++;
            this->y++;
            return *this;
        }

        Point& operator ++(int value)
        {
            Point temp(*this);

            this->x++;
            this->y++;

            return temp;
        }

        Point& operator --()
        {
            this->x--;
            this->y--;
            return *this;
        }

        Point& operator --(int value)
        {
            Point temp(*this);

            this->x--;
            this->y--;

            return temp;
        }

    private:
        int x;
        int y;

        friend void ChangeX(Point& value);
    };

    void ChangeX(Point& value)
    {
        value.x = -1;
    }

}

namespace n90
{
    /*дружественные методы класса*/

    class Apple;

    class Human
    {
    public:
        void TakeApple(Apple& apple);
    };

    class Apple
    {
    public:
        Apple(int weight,std::string color)
        {
            this->weight = weight;
            this->color = color;
        }

    private:
        int weight;
        std::string color;

        friend void Human::TakeApple(Apple& apple);

    };

    void Human::TakeApple(Apple& apple)
    {
        std::cout << "TakeApple Color = " << apple.color << " weight = " << apple.weight << std::endl;
    }
}

namespace n91
{
    /*дружественные методы класса
    
        n91::Apple app(150, "red");
        n91::Human human;

        human.TakeApple(app);
    
    */

    class Apple;

    class Human
    {
    public:
        void TakeApple(Apple& apple);
        void EatApple(Apple& apple)
        {

        }
    };

    class Apple
    {
        friend Human;
    public:
        Apple(int weight, std::string color)
        {
            this->weight = weight;
            this->color = color;
        }

    private:
        int weight;
        std::string color;
    };

    void Human::TakeApple(Apple& apple)
    {
        std::cout << "TakeApple Color = " << apple.color << " weight = " << apple.weight << std::endl;
    }
}

namespace n92
{
    /*
            n92::Apple app(150, "red");
            n92::Apple app1(100, "green");
            n92::Apple app2(200, "yellow");
    
            std::cout << n92::Apple::count;
    */
    class Apple
    {
    public:

        static int count;

        Apple(int weight, std::string color)
        {
            this->weight = weight;
            this->color = color;
            count++;
        }

    private:
        int weight;
        std::string color;
    };

    int Apple::count = 0;
}

namespace n93
{
    /*
        n93::Apple app(150, "red");
        n93::Apple app1(100, "green");
        n93::Apple app2(200, "yellow");

        std::cout << app.GetId()<<std::endl;
        std::cout << app1.GetId()<< std::endl;
        std::cout << app2.GetId() << std::endl;

    */
    class Apple
    {
    public:

        static int count;

        Apple(int weight, std::string color)
        {
            this->weight = weight;
            this->color = color;
            count++;
            id = count;
        }

        int GetId()
        {
            return id;
        }

    private:
        int weight;
        int id;
        std::string color;
    };

    int Apple::count = 0;
}

namespace n94
{
    /*
        n94::Apple app(150, "red");
        n94::Apple app1(100, "green");
        n94::Apple app2(200, "yellow");

        std::cout << app.GetCount();

        n94::Apple::ChangetColor(app, "green");
    */
    class Apple
    {
    public:
        Apple(int weight, std::string color)
        {
            this->weight = weight;
            this->color = color;
            count++;
            id = count;
        }

        int GetId()
        {
            return id;
        }

        static int GetCount()
        {
            return count;
        }

        static void ChangetColor(Apple& apple, std::string color)
        {
            apple.color = color;
        }


        void ChangetColorNoStatic(std::string color)
        {
            this->color = color;
        }

    private:
        static int count;
        int weight;
        int id;
        std::string color;
    };

    int Apple::count = 0;
}

namespace n95
{
    /*
        n95::Image image;

        image.GetImageInfo();
    */
    class Image
    {

    public:

        void GetImageInfo()
        {
            for (int i = 0; i < length; i++)
            {
                std::cout  << "#" << i << pixel[i].GetInfo() << std::endl;
            }
        }

        class Pixel
        {
        public:
            Pixel(int r, int g, int b)
            {
                this->r = r;
                this->g = g;
                this->b = b;
            }
            std::string GetInfo()
            {
                return " Pixel: r = " + std::to_string(r) + " g = " + std::to_string(g) + " b = " + std::to_string(b);
            }

        private:
            int r;
            int g;
            int b;
        };
    private:

        static const int length = 5;
        
        Pixel pixel[length]
        {
            Pixel(23,34,23),
            Pixel(33,36,83),
            Pixel(56,24,29),
            Pixel(23,37,52),
            Pixel(83,54,43)
        };

    };

}

namespace n96
{
    /*
        using namespace n96;

        //статический массив
        const int length = 5;
        Pixel pixel1[length]
        {
            Pixel(23,34,23),
            Pixel(33,36,83),
            Pixel(56,24,29),
            Pixel(23,37,52),
            Pixel(83,54,43)
        };
        std::cout << pixel1[2].GetInfo() << std::endl;

        //Динамический массив
        int length2 = 6;
        Pixel* pixel2 = new Pixel[length2];
        for (int i = 0; i < length2; i++)
        {
            int a = rand() % 255 - 10;
            int b = rand() % 255 - 10;
            int c = rand() % 255 - 10;
            pixel2[i] = Pixel(a, b, c);
        }

        for (int i = 0; i < length2; i++)
        {
            std::cout << pixel2[i].GetInfo() << std::endl;
        }
    */

    class Pixel
    {
    public:

        Pixel()
        {
            r = g = b = 0;
        }

        Pixel(int r, int g, int b)
        {
            this->r = r;
            this->g = g;
            this->b = b;
        }
        std::string GetInfo()
        {
            return " Pixel: r = " + std::to_string(r) + " g = " + std::to_string(g) + " b = " + std::to_string(b);
        }

    private:
        int r;
        int g;
        int b;
    };



}

namespace n97
{
    //когда человек вызывает мозг(а именно мозг думает) - композиция( жестко привязан)
   //агрегция - не жестко привязан


    class Cap
    {
    public:
        std::string getColor()
        {
            return color;
        }

    private:
        std::string color = "red";
    };

    class Model
    {
    public:

    };

    class  Human
    {
    public:
        void Think()
        {
            brain.Think();
        }
        void inspectCap()
        {
            std::cout << "У меня кепка: " << cap.getColor()<<std::endl;
        }

    private:
        class Brain
        {

        public:
            void Think()
            {
                std::cout << " Я думаю! " << std::endl;
            }

        };

        Brain brain;
        Cap cap;
    };


}

int main()
{
    setlocale(LC_ALL, "Ru");

    using namespace n97;
    Human human;

    human.Think();

    return 0;
}
