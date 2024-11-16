from ._litenet_core import Tensor as _CTensor

class Tensor:
    def __init__(self, shape):
        self._tensor = _CTensor(shape)

    def __repr__(self):
        return f"Tensor(shape={self.shape})"

    @property
    def shape(self):
        return self._tensor.shape
