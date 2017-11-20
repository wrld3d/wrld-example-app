# http://stackoverflow.com/a/1123054/83891
# hacky python equivalent of c# anonymous types.  Very useful for defining test cases for data driven testing.
class TestData:
    def __init__(self, **entries):
        self.__dict__.update(entries)
        self.description = "no description"

    def with_description(self, description):
        self.description = description
        return self