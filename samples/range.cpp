#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>

namespace detail {
    /** Container agnostic iterators. */
    template<typename T>
    class RangeIterator {
    private:
        // We need an abstract class to erase the type of the iterator.
        struct iterator_base {
            virtual iterator_base& operator ++ () = 0;
            virtual T& operator * () const = 0;
            virtual bool operator != (iterator_base const& other) const = 0;
            virtual ~iterator_base() {};
        };
        
        template<typename ConcreteIterator>
        struct iterator_implementation : iterator_base {
            ConcreteIterator concrete_iterator;
            
            iterator_implementation(ConcreteIterator && concrete_iterator)
                : concrete_iterator(std::move(concrete_iterator))
            {}
            
            iterator_base& operator ++ () override {
                ++concrete_iterator;
                return *this;
            }
            
            T& operator * () const override {
                return *concrete_iterator;
            }
            
            bool operator != (iterator_base const& other) const override {
                return this->concrete_iterator != dynamic_cast<const iterator_implementation*>(&other)->concrete_iterator;
            }
        };
    
    public:
        struct iterator {
            std::unique_ptr<iterator_base> base_iterator;
            template<typename IteratorType>
            iterator(IteratorType && it) : base_iterator(std::make_unique<iterator_implementation<typename std::remove_reference<IteratorType>::type>>(std::move(it))) {}
            
            iterator& operator ++ () { ++(*base_iterator); return *this; }
            T& operator * () const { return *(*base_iterator); }
            bool operator != (iterator const& other) const { return *base_iterator != *other.base_iterator; }
        };
    };
}



/** Implementation agnostic container. */
template<typename T>
class Container : public detail::RangeIterator<T>
{
public:
    using iterator = typename Container::iterator;
private:
    // Similarly we need an abstract class to hold any container.
    struct container_base {
        virtual iterator begin() = 0;
        virtual iterator end() = 0;
        virtual ~container_base() {}
    };
    
    template<typename ConcreteContainer>
    struct container_implementation : container_base {
        ConcreteContainer concrete_container;
        container_implementation(ConcreteContainer && concrete_container) : concrete_container(std::move(concrete_container)) {}
        
        iterator begin() override { return iterator(concrete_container.begin()); }
        iterator end() override { return iterator(concrete_container.end()); }
    };
    
    std::shared_ptr<container_base> container;
    
public:
    
    iterator begin() { return container->begin(); }
    iterator end() { return container->end(); }
    
    /** Contruct from a range; taking control over it. */
    template<typename ConcreteContainer>
    Container(ConcreteContainer && concrete_container) 
        : container(std::make_shared<container_implementation<ConcreteContainer>>(std::move(concrete_container)))
    {}
};

template<typename ConcreteContainer>
Container<typename ConcreteContainer::value_type> container(ConcreteContainer && concrete_container) {
    return Container<typename ConcreteContainer::value_type>(std::forward<ConcreteContainer>(concrete_container));
}

/** Container agnostic range. */
template<typename T>
class Range : public detail::RangeIterator<T>
{
public:
    using iterator = typename Range::iterator;
private:
    iterator begin_iterator;
    iterator end_iterator;
    
public:
    
    iterator& begin() { return begin_iterator; }
    iterator& end() { return end_iterator; }
    
    /** Contruct from a range; note that the underlying container must remain alive. */
    template<typename ConcreteContainer>
    Range(ConcreteContainer && concrete_container) 
        : begin_iterator(concrete_container.begin())
        , end_iterator(concrete_container.end())
    {}
};

template<typename ConcreteContainer>
Range<typename ConcreteContainer::value_type> range(ConcreteContainer && concrete_container) {
    return Range<typename ConcreteContainer::value_type>(std::forward<ConcreteContainer>(concrete_container));
}

int main()
{
    std::vector<Container<int>> containers{
        std::vector<int>{1, 2, 3},
        std::list<int>{4, 5, 6}
    };

    for (auto && container : containers) {
        std::cout << "Container: ";
        for (auto x : container) {
            std::cout << x << "; ";
        }
        std::cout << std::endl;
    }
    
    auto print_ints = [](Range<int> r) {
        std::cout << "Ints: ";
        for (auto x : r) {
            std::cout << x << "; ";
        }
        std::cout << std::endl;
    };
    
    print_ints(std::vector<int>{7, 8 , 9});
}