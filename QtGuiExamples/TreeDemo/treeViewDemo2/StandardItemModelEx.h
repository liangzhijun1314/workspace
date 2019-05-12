#ifndef STANDARDITEMMODELEX_H
#define STANDARDITEMMODELEX_H
#include <QStandardItemModel>
#include <functional>
#include <iostream>
using namespace std;

class StandardItemModelEx
 {
 public:
       StandardItemModelEx(){}
       ~StandardItemModelEx(){}
//       typedef std::function<void(QStandardItem*)> callback_ergodicFun_ptr;

//       typedef std::function<void(QStandardItem*)> callback_ergodicFun_ptr;
       static void ergodicAllItem(QStandardItemModel* model/*,callback_ergodicFun_ptr pFun*/)
       {
           int rows = model->rowCount();
              int column = model->columnCount();
              for (int i=0;i<rows;++i)
              {
                  for(int j=0;j<column;++j)
                  {
                      QStandardItem* item = model->item(i,j);
                      if (item)
                      {
                          ergodicItem(item/*,pFun*/);
                      }
                  }
              }
       }

       static void ergodicItem(QStandardItem* item/*,callback_ergodicFun_ptr pFun*/)
       {
           int rows = item->rowCount();
           int column = item->columnCount();
           for (int i=0;i<rows;++i)
           {
               for(int j=0;j<column;++j)
               {
                   QStandardItem* childItem = item->child(i,j);
                   if (childItem)
                   {
                       ergodicItem(childItem/*,pFun*/);
                   }
               }
           }
//           pFun(item);
       }

private:
 };
#endif // STANDARDITEMMODELEX_H
