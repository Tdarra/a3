#ifdef _STOCKSYSTEM_H_


StockSystem::StockSystem() {
	balance = 100,000.00;
}

double StockSystem::GetBalance(){return balance;}

bool StockSystem::StockNewItem(StockItem item){
	return false; //FIXME
}

bool StockSystem::EditStockItemDescription(int itemsku, string desc){
	return false; //FIXME
}

bool StockSystem::EditStockItemPrice(int itemsku, double retailprice){
		return false; //FIXME
}

bool StockSystem::Restock(int itemsku, int quantity, double unitprice){
		return false; //FIXME

}

bool StockSystem::Sell(int itemsku, int quantity){
	return false; //FIXME
}

#endif






