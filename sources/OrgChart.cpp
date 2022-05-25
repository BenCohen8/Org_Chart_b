
#include "OrgChart.hpp"
#include <iostream>
using namespace std;
using namespace ariel;


   
      OrgChart OrgChart::add_root(const string& s)
      {
        this->setroot(s); 
        return *this;
      }
        OrgChart OrgChart::add_sub(const string& s1,const string &s2)
        {
          if (this->getRoot()==nullptr)
          {
            string er="cant add sub before root";
            throw er;
          }
          
        employee * tw=find(s1,getRoot());
        if (tw!=nullptr)
        {
          if (tw->son!=nullptr)
          {
              employee *t=tw->son;  
             while (t->bro!=nullptr)
              {
               t=t->bro;
              }
             t->bro= new employee(s2);
              t->bro->dad=tw;
              t->bro->h=t->h;
          }else
          {
            tw->son=new employee(s2);
            tw->son->dad=tw;
            employee *e=tw->son;
            e->h=tw->h+1;
            if (e->h>this->hoc)
            {
               this->getRoot()->hoc=e->h;
               this->hoc=e->h;
            } 
          }   
        }else
        {
	         string ex="not a valid code";
            throw ex;  
        }
        return *this;
        }

      employee * OrgChart::find(const string& e,employee *root)
      {
        if(root==nullptr)
        {
          return nullptr;
        }
        if (root->Name==e)
        {
          return root;
        }
        
        
          employee *em=find(e,root->bro);
          if (em==nullptr)
          {
            em=find(e,root->son);
          }
          return em;
        
        
        return nullptr;
      }

/////////level iterator////////////
///////////////////////////////////
		string OrgChart::iterator::operator*()  {

 			return level[0]->Name;
		}



		// ++i;
		OrgChart::iterator& OrgChart::iterator::operator++() {
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



		bool OrgChart::iterator::operator==(const iterator& rhs) const {
			return root == rhs.root;
		}

		bool OrgChart::iterator::operator!=(const iterator& rhs) const {
			return root != rhs.root;
		}
			employee*  OrgChart::iterator::operator->() 
			{
				return this->root;
			}
/////////////////////////////////////////
      ////////end level iterator/////////
/////////////////////////////////////////

/////////////////////////////////////////
///////////start pre iterator////////////
/////////////////////////////////////////

 string OrgChart::pre_iterator::operator*() const {
			return this->root->Name;
		}
		
		// ++i;
	OrgChart::pre_iterator&  OrgChart::pre_iterator::operator++() {
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
			employee*  OrgChart::pre_iterator::operator->() 
			{
				return this->root;
			}

		bool OrgChart::pre_iterator::operator==(const pre_iterator& rhs) const {
			return root == rhs.root;
		}

		bool OrgChart::pre_iterator::operator!=(const pre_iterator& rhs) const {
			return root != rhs.root;

		}
/////////////////////////////////////////
///////////end pre iterator////////////
/////////////////////////////////////////

/////////////////////////////////////////
///////////start reverse iterator////////////
/////////////////////////////////////////


		 string OrgChart::reverse_iterator::operator*() const {
			//return *pointer_to_current_node;
			return this->root->Name;
		}		
		// ++i;
		OrgChart::reverse_iterator& OrgChart::reverse_iterator::operator++() {
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


		bool OrgChart::reverse_iterator::operator==(const reverse_iterator& rhs) const {
			return root == rhs.root;
		}

		bool OrgChart::reverse_iterator::operator!=(const reverse_iterator& rhs) const {
			return root != rhs.root;

		}
		employee*  OrgChart::reverse_iterator::operator->() 
		{
			return this->root;
		}

/////////////////////////////////////////
///////////end reverse iterator////////////
/////////////////////////////////////////