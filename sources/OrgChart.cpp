
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
             t->bro->son=nullptr;
             t->bro->bro=nullptr;

          }else
          {
          tw->son=new employee(s2);
          tw->son->son=nullptr;
          tw->son->bro=nullptr;
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
