# Import the compiled C extension
import litenet

class Tensor:
    def __init__(self, shape):
        # Create a Tensor object using the C extension
        self._tensor = litenet.Tensor(shape)

    def __repr__(self):
        return f"Tensor(shape={self.shape})"

    @property
    def shape(self):
        # Access the shape of the tensor
        return self._tensor.shape

    # Add more methods as needed to interface with the C extension
