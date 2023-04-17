from shopping import ShoppingCart

def test_add_products():
    cart = ShoppingCart()
    assert (cart.get_total()==0)
    cart.add_product("apple", 2)
    assert (cart.get_total()==2)
    cart.add_product("orange", 3)
    assert (cart.get_total()==5)