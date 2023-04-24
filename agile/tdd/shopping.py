class Product:
    def __init__(self, name, price):
        self.name = name
        self.price = price

class ShoppingCart:
    def __init__(self):
        self.products = []
    def get_total(self):
        return sum([product.price for product in self.products])
    def add_product(self, product, price):
        self.products.append(Product(product, price))
