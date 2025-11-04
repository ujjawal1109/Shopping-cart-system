# streamlit_app.py

import streamlit as st

class Product:
    def __init__(self, pid, name, price):
        self.id = pid
        self.name = name
        self.price = price

class CartItem:
    def __init__(self, product, quantity):
        self.product = product
        self.quantity = quantity
    
    def get_total_price(self):
        return self.product.price * self.quantity

class ShoppingCart:
    def __init__(self):
        self.items = []

    def add_item(self, product, qty):
        # If already in cart, increase quantity
        for item in self.items:
            if item.product.id == product.id:
                item.quantity += qty
                return
        self.items.append(CartItem(product, qty))
    
    def view_cart(self):
        total = 0
        if not self.items:
            st.info("Cart is empty!")
            return 0
        for item in self.items:
            st.write(f"{item.product.name} x {item.quantity} = ₹{item.get_total_price():.2f}")
            total += item.get_total_price()
        st.write(f"**Total: ₹{total:.2f}**")
        return total

# Initialize products
products = [
    Product(1, "Laptop", 55000),
    Product(2, "Smartphone", 25000),
    Product(3, "Headphones", 2000),
    Product(4, "Smartwatch", 5000)
]

# Session state for user/cart
if 'username' not in st.session_state:
    st.session_state.username = ""
if 'cart' not in st.session_state:
    st.session_state.cart = ShoppingCart()

# ---- User Input ----
st.title("🛒 Simple Shopping Cart App")
if not st.session_state.username:
    username = st.text_input("Enter your name:")
    if username:
        st.session_state.username = username
        st.success(f"Welcome, {username}!")
else:
    st.write(f"Hello, **{st.session_state.username}**!")

    menu = st.sidebar.selectbox("Menu", ["View Products", "Add to Cart", "View Cart", "Checkout & Exit"])

    if menu == "View Products":
        st.subheader("Product List")
        for product in products:
            st.write(f"**ID:** {product.id} | {product.name} | Price: ₹{product.price}")
    elif menu == "Add to Cart":
        st.subheader("Add Product to Cart")
        product_ids = [p.id for p in products]
        product_names = [f"{p.name} (₹{p.price})" for p in products]

        selected_product_idx = st.selectbox("Select Product", range(len(product_names)),
                                            format_func=lambda x: product_names[x])
        qty = st.number_input("Enter Quantity", min_value=1, value=1)

        if st.button("Add to Cart"):
            prod = products[selected_product_idx]
            st.session_state.cart.add_item(prod, qty)
            st.success(f"{prod.name} (x{qty}) added to cart.")
    elif menu == "View Cart":
        st.subheader("Your Cart")
        st.session_state.cart.view_cart()
    elif menu == "Checkout & Exit":
        st.subheader(f"Thank you for shopping with us, {st.session_state.username}!")
        st.session_state.cart.view_cart()
        st.info("Reload the page to shop again.")

# Instructions for running:
# 1. Save this file as 'streamlit_app.py'
# 2. Install streamlit: pip install streamlit
# 3. Run with: streamlit run streamlit_app.py
