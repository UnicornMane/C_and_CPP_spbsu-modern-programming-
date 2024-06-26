#include "Scheme.hpp"
#include <stdexcept>
#include <cmath>

Scheme::Scheme(int capacity)
{
    size_ = 0;
    capacity_ = capacity;
    figures_ = new Figure*[capacity];
}
Scheme::~Scheme()
{
    for (size_t i = 0; i < size_; ++i)
    {
        delete figures_[i];
    }

    delete[] figures_;
}

void Scheme::push_back_figure(Figure* fg)
{
    if (size_ + 1 > capacity_)
    {
        throw std::out_of_range("You can't add more elements!");
    }

    ++size_;
    figures_[size_ - 1] = fg;
}

void Scheme::swap(Figure*& a, Figure*& b)
{
    Figure* temp = a;
    a = b;
    b = temp;
}

void Scheme::remove_figure(int id)
{
    int targetIndex = getIndexById(id);
    if (targetIndex == -1)
    {
        throw std::invalid_argument("There is no such element!");
    }

    for (size_t i = targetIndex; i < size_ - 1; ++i)
    {
        swap(figures_[i], figures_[i + 1]);
    }
    delete figures_[size_ - 1];
    --size_;
}

void Scheme::print_all_figures()
{
    for (size_t i = 0; i < size_; ++i)
    {
        figures_[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor)
{
    int targetIndex = getIndexById(id);
    if (targetIndex == -1)
    {
        throw std::invalid_argument("There is no such element!");
    }

    figures_[targetIndex]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y)
{
    for (size_t i = 0; i < size_; ++i)
    {
        if (figures_[i]->is_inside(x, y))
        {
            return figures_[i];
        }
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y)
{
    int targetIndex = getIndexById(id);
    if (targetIndex == -1)
    {
        throw std::invalid_argument("There is no such element!");
    }

    figures_[targetIndex]->move(new_x, new_y);
}

int Scheme::getIndexById(int id) const
{
    for (size_t i = 0; i < size_; ++i)
    {
        if (figures_[i]->getId() == id)
        {
            return i;
        }
    }
    return -1;
}