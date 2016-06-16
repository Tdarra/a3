#ifdef _STOCKSYSTEM_H_


StockSystem::StockSystem() : records(), balance(100000) {}

double StockSystem::GetBalance(){return balance;}

bool StockSystem::StockNewItem(StockItem item){
    return records.Insert(item);
}

bool StockSystem::EditStockItemDescription(int itemsku, string desc){
    StockItem item(itemsku, "", 0);

    if(records.Contains(item)){
        StockItem* found = records.Retrieve(item);
        return found->SetDescription(desc);
    }
    else
        return false;
}

bool StockSystem::EditStockItemPrice(int itemsku, double retailprice){
    StockItem item(itemsku, "", 0);

    if (records.Contains(item) && retailprice >= 0){
        StockItem* found = records.Retrieve(item);
        return found->SetPrice(retailprice);
    }
    else
        return false;

}

bool StockSystem::Restock(int itemsku, int quantity, double unitprice){
    if (quantity < 0 || unitprice < 0)
        return false;
    double totalcost = quantity * unitprice;
    StockItem item(itemsku, "", 0);
    double newbalance = balance - totalcost;
    if (records.Contains(item) && newbalance >= 0){
        StockItem* found = records.Retrieve(item);
        balance = newbalance;
        int amount = found->GetStock() + quantity;
        return found->SetStock(amount);
    }
    else
        return false;
}

bool StockSystem::Sell(int itemsku, int quantity){
    StockItem item(itemsku, "", 0);

    if (records.Contains(item) && quantity >= 0){
        StockItem* found = records.Retrieve(item);
        int stock = found->GetStock();
        if (stock == 0)
            return false;
        else if (quantity > stock){
            double price = found->GetPrice();
            balance = balance + stock*price;
            stock = 0;
            }
        else{
            double price = found->GetPrice();
            balance = balance + quantity*price;
            stock -= quantity;
            }

        return found->SetStock(stock);
        }
    else
        return false;
    }

#endif






