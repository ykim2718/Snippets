"""
y, 2025.4.25
copilot
python function - callback wrapper.py
"""


# Define a class to add callback functionality
class CallbackWrapper:
    def __init__(self, func, callback=None):
        self.func = func
        self.callback = callback

    def __call__(self, *args, **kwargs):
        # Call the original function
        result = self.func(*args, **kwargs)
        # Call the callback function, if provided
        if self.callback:
            self.callback(result)
        return result


# Define a sample callback function
def my_callback(result):
    print(f"Callback received result: {result}")


# Define a function to be wrapped
def multiply(a, b):
    return a * b


# Wrap the function using the class and provide the callback
wrapped_function = CallbackWrapper(multiply, my_callback)

# Call the wrapped function
wrapped_function(3, 4)
