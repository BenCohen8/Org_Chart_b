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
		//employee* pointer_to_current_node;
		employee *root;

	public:
		iterator(employee* ptr = nullptr)
			 {
			root=ptr;
			level.push_back(root);
		}


		string operator*()  {

 			return level[0]->Name;
		}



		// ++i;
		iterator& operator++() {
			if (!level.empty())
			{
				employee *e=level[0];
				if (e->son!=nullptr)
				{
				employee * son=e->son;
				level.push_back(son);
				while (son->bro!=nullptr)
				{
					level.push_back(son->bro);
					son=son->bro;
				}
				}
				level.erase(level.begin());
				if(level.empty())
				{
					root=nullptr;
				}else{

				root=level[0];
				}
			}else
			{
				 root=nullptr;
			}

				
			
			return *this;
		}



		bool operator==(const iterator& rhs) const {
			return root == rhs.root;
		}

		bool operator!=(const iterator& rhs) const {
			return root != rhs.root;
		}
			employee*  operator->() 
			{
				return this->root;
			}
  	};  // END OF CLASS ITERATOR

	class pre_iterator {

	  private:
		employee* root;
	public:

		pre_iterator(employee* ptr = nullptr)
			: root(ptr) {
		}

		 string operator*() const {
			return this->root->Name;
		}
		
		// ++i;
		pre_iterator& operator++() {
			if (root->son!=nullptr)
			{
				root=root->son;
				return *this;

			} if (root->bro!=nullptr)
			{
				root=root->bro;
				return *this;

			} if (root->dad!=nullptr)	
			{

				root=root->dad;
				while (root->bro==nullptr)
				{
					if (root->h>1){
					root=root->dad;
					}else
					{
						root=nullptr;
						return *this;
					}
				}
																										

				root=root->bro;
				return *this;

			}
			if (root->dad==nullptr)
			{
		
			
			root=nullptr;
			return *this;
			}
			return *this;
		}

		// i++;

			employee*  operator->() 
			{
				return this->root;
			}

		bool operator==(const pre_iterator& rhs) const {
			return root == rhs.root;
		}

		bool operator!=(const pre_iterator& rhs) const {
			return root != rhs.root;

		}

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

		 string operator*() const {
			//return *pointer_to_current_node;
			return this->root->Name;
		}

		
		// ++i;
		reverse_iterator& operator++() {
			if (root->h==_h&&_h>1)
			{
				if (root->bro!=nullptr)
				{
					root=root->bro;
					return *this;
				}
				
					root=root->dad;
					while (root->bro==nullptr&&root->h>1)
					{
						root=root->dad;
					}
					if (root->h>1)
					{
						root=root->bro;
					}
					else
					{
						_h--;
						if (_h==1)
						{
							root=ce;
							return *this;
						}
						
					}
					
					
				
				
			}
			if (_h==1)
			{
				root=nullptr;
				return *this;
			}
			while (this->root->h<_h)
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
				while (root->bro==nullptr&&root!=ce)
				{
					root=root->dad;
				}
				
				if (root==ce)
				{
					_h--;
				}
				else
				{
					root=root->bro;
				}
			}				
			}

			return *this;
		}
		// i++;
		// Usually iterators are passed by value and not by const& as they are small.


		bool operator==(const reverse_iterator& rhs) const {
			return root == rhs.root;
		}

		bool operator!=(const reverse_iterator& rhs) const {
			return root != rhs.root;

		}
		employee*  operator->() 
		{
			return this->root;
		}
		
	};  // END OF CLASS const_iterator


	 iterator  begin()const {
		return iterator{m_first};
	}
	
		 iterator static end() {
		// return nullptr; 
		return iterator{nullptr};
	}
	//////////
	
	OrgChart::pre_iterator    begin_preorder()const	
    {
      if (this->getRoot()==nullptr)
      {
        throw "Empty error";
      }
        return pre_iterator{getRoot()};
      }
		 OrgChart::pre_iterator  end_preorder()const
		 {
			if (this->getRoot()==nullptr)
      	{
        	throw "Empty error";
      	}
      
          return pre_iterator{nullptr};
		 }
	    OrgChart::iterator  begin_level_order()const
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


