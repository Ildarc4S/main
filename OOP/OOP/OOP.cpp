#include <iostream>

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

int main()
{

    return 0;
}
