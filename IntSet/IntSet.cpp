// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     compile-time array whose size is IntSet::MAX_SIZE;
//     the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[IntSet::MAX_SIZE - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

IntSet::IntSet()
{
   used = 0;
   data[MAX_SIZE] = {0};
}

int IntSet::size() const
{
   return used; //returns current size of integer set
}


bool IntSet::isEmpty() const
{
    if(size() == 0)
       return true;
}

bool IntSet::contains(int anInt) const
{
   if(used > 0)
   {
       for(int i = 0; i < used; ++i)
       {
           if(data[i] == anInt)
            return true;
       }
   }
   return 0;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
    int counter = 0;

    IntSet subSet;

    for(int i = 0; i < used; ++i)
        subSet.add(data[i]); //copy integers and size from object being
                             //operated on

    if(isEmpty())
        return true;

    else
    {
        for(int i = 0; i < used; ++i)
        {
            if(otherIntSet.contains(subSet.data[i]))
            ++counter;
        }

        if(counter == used)
        {
            counter = 0;
            return true;
        }
    }

    return false;
}

void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
    IntSet unionSet;

    for(int i = 0; i < used; ++i)
        unionSet.add(data[i]);

    if((used + otherIntSet.subtract(unionSet).size()) <= MAX_SIZE)
    {
        for(int i = 0; i < otherIntSet.size(); ++i)
        {
            if(!unionSet.contains(otherIntSet.data[i]))
                unionSet.add(otherIntSet.data[i]);
        }
    }
    return unionSet;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
    IntSet interSet;

    for(int i = 0; i < used; ++i)
        interSet.add(data[i]);

    for(int i = 0; i < interSet.size(); ++i)
    {
        if(!otherIntSet.contains(interSet.data[i])) //check if int in both
            interSet.remove(interSet.data[i]);
    }
    return interSet;
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
    IntSet subtractSet;

    for(int i = 0; i < used; ++i)
        subtractSet.add(data[i]);

    for(int i = 0; i < otherIntSet.size(); ++i)
    {
        if(subtractSet.contains(otherIntSet.data[i]))
        {
            subtractSet.remove(otherIntSet.data[i]);
            --subtractSet.used;
        }
    }

   return subtractSet;
}

void IntSet::reset()
{
   used = 0;
}

bool IntSet::add(int anInt)
{
   if(used >= MAX_SIZE)
   {
       cout << "No more space available in integer set, delete an int and try"
            << " again." << endl;

       return true;
   }

   else
   {
        if(contains(anInt)) //only one copy of integer in set
        return false;

        else
        {
            data[used] = anInt;
            ++used;
            return true;
        }
   }
   return false;
}

bool IntSet::remove(int anInt)
{
    if(contains(anInt))
    {
        for(int i = 0; i < used; ++i)
        {
            if(data[i] == anInt)
            {
                for(int j = i; j < (used - 1); ++j) //subtract 1 to protect
                    data[j] = data[j + 1];          //from out of bounds
            }
        }

        --used;
        return true;
    }

   return false;
}

bool equal(const IntSet& is1, const IntSet& is2)
{
   if(is1.isSubsetOf(is2) && is2.isSubsetOf(is1))
    return true;

   else
   return false;
}
