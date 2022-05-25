#include <iostream>
#include <vector>
using namespace std;
#pragma once
namespace ariel{

struct employee
	{
	employee *bro;
	employee *son;
	employee * dad;
	int h=0;
	int hoc;


	public:
	    string Name;
		
		friend std::ostream & operator<< (std::ostream &stream, const  employee &employee ){stream<<employee.Name;return stream;}
		int   size()const{return Name.size();}
		int length()const{return size();}
		char at(size_t i)const{return Name.at(i);}
		void setName(string v)
		{
			this->Name=move(v);
		}
	

	employee( string v)
	{
		this->bro=nullptr;
		this->son=nullptr;
		this->dad=nullptr;
		this->bro=nullptr;
		this->hoc=0;

		this->Name=move(v);
	}
	};

class OrgChart {
	
	
	public:
	int hoc=0;	
	employee* m_first=nullptr;
	void setroot(const string &e)
	{	
		if (!isEmpty())
		{
			this->getRoot()->setName(e);
			return;
		}
		
		this->m_first=new employee(e);
		m_first->h=1;
		this->hoc=1;
		m_first->dad=nullptr;
	
	}
		void setroot(employee *e)
	{
		this->m_first=e;
	}
    OrgChart(OrgChart,OrgChart);

	OrgChart() : m_first(nullptr) {
	}

	OrgChart add_root(const string &s);

    OrgChart  add_sub(const string&,const string&);

	bool isEmpty() const {
		return m_first==nullptr;
	}
	 employee * getRoot() const{
		return m_first;
	}
	friend std::ostream & operator<< (std::ostream &stream, const  OrgChart &oc )
	{
		bool first=true;
		int i=0;
		auto it1=oc.begin_level_order();
		for (auto it =oc.begin_level_order(); it!=oc.end_level_order(); ++it)
		{
			if (first)
			{
				first=false;
				stream<<i<<")"<<(*it);
			}else 
			{

				if (it1->h<it->h)
				{
					i=0;
					stream<<"\n"<<i<<")"<<(*it);
				}else if (it1->bro==nullptr)
				{
					i++;
					stream<<" \t"<<i<<")"<<(*it);
				}else
				{
					stream<<"\t"<<(*it);
				}
				++it1;

			}


		}
		stream<<endl;
		return stream;
	}
	employee *find(const string&,employee*);


	
	class iterator {
	  	private:
		vector<employee*> level;
		employee *root;

	public:
		iterator(employee* ptr = nullptr)
		{
			root=ptr;
			level.push_back(root);
		}
		string operator*();
		// ++i;
		iterator& operator++();
		bool operator==(const iterator& rhs) const ;
		bool operator!=(const iterator& rhs) const ;
		employee*  operator->() ;
  		};  // END OF CLASS ITERATOR

	class pre_iterator {
		 private:
			employee* root;
		public:
			pre_iterator(employee* ptr = nullptr)
				: root(ptr) {
			}

			string operator*() const;
			pre_iterator& operator++();		// ++i;
			employee*  operator->();
			bool operator==(const pre_iterator& rhs) const;

			bool operator!=(const pre_iterator& rhs) const;

	};  // END OF CLASS pre_iterator
class reverse_iterator {

	  private:
		employee* root;
		employee *ce;
		int _h;
	public:

		reverse_iterator(employee* ptr ,int h)
		{
			this->_h=h;
			 root=ptr;	
			 if (root!=nullptr)
			 {
		
			 
			while (root!=nullptr&&root->h<_h)
			{
			if (root->son!=nullptr)
			{
				root=root->son;

			}else if (root->bro!=nullptr)
			{
				root=root->bro;
			}else if (root->dad!=nullptr)	
			{
				root=root->dad;
				while (root->bro==nullptr&&root->h>1)
				{
					root=root->dad;
				}
			
					root=root->bro;
					
			}
			}
			 }
			ce=ptr;
		}

		 string operator*() const;

		
		// ++i;
		reverse_iterator& operator++();
		

		bool operator==(const reverse_iterator& rhs) const ;
		

		bool operator!=(const reverse_iterator& rhs) const ;
		employee*  operator->() ;
		
	};  // END OF CLASS reverse_iterator


	 iterator  begin()const {
		return iterator{m_first};
	}
	
		 iterator static end() {
		// return nullptr; 
		return iterator{nullptr};
	}
	
	pre_iterator    begin_preorder()const	
    {
      if (this->getRoot()==nullptr)
      {
        throw "Empty error";
      }
        return pre_iterator{getRoot()};
      }
		 pre_iterator  end_preorder()const
		 {
			if (this->getRoot()==nullptr)
      	{
        	throw "Empty error";
      	}
      
          return pre_iterator{nullptr};
		 }
	    iterator  begin_level_order()const
		{
    
	    if (this->getRoot()==nullptr)
		{
			throw "Empty error";
		}
		
		return begin();
		
		} 
	    OrgChart::iterator   end_level_order()const
		{
       
        if (this->getRoot()==nullptr)
		{
    	    throw "Empty error";
      	}		
        return end();
		}
		

		OrgChart::reverse_iterator   begin_reverse_order()const
         { 
            if (this->getRoot()==nullptr)
            {
              throw "Empty error";
            }
          return reverse_iterator{this->getRoot(),this->getRoot()->hoc};
     
          }
		OrgChart::reverse_iterator  reverse_order()const
		{
        if (this->getRoot()==nullptr)
      {
        throw "Empty error";
      }
      
            return reverse_iterator{nullptr,this->hoc};
		}


};


}


