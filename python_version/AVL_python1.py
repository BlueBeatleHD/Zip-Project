import os
import csv
import time

class AVLNode:
    def __init__(self, population, zipcode):
        self.population = population
        self.zipcode = zipcode
        self.left = None
        self.right = None
        self.height = 1

class AVLTree:
    def __init__(self):
        self.root = None

    def insert(self, population, zipcode):
        self.root = self._insert_helper(self.root, population, zipcode)

    def _insert_helper(self, node, population, zipcode):
        if not node:
            return AVLNode(population, zipcode)

        if population < node.population:
            node.left = self._insert_helper(node.left, population, zipcode)
        elif population > node.population:
            node.right = self._insert_helper(node.right, population, zipcode)
        else:
            return node

        node.height = 1 + max(self._get_height(node.left), self._get_height(node.right))

        balance = self._get_balance(node)

        if balance > 1 and population < node.left.population:
            return self._right_rotate(node)

        if balance < -1 and population > node.right.population:
            return self._left_rotate(node)

        if balance > 1 and population > node.left.population:
            node.left = self._left_rotate(node.left)
            return self._right_rotate(node)

        if balance < -1 and population < node.right.population:
            node.right = self._right_rotate(node.right)
            return self._left_rotate(node)

        return node

    def _right_rotate(self, z):
        y = z.left
        T3 = y.right

        y.right = z
        z.left = T3

        z.height = 1 + max(self._get_height(z.left), self._get_height(z.right))
        y.height = 1 + max(self._get_height(y.left), self._get_height(y.right))

        return y

    def _left_rotate(self, z):
        y = z.right
        T2 = y.left

        y.left = z
        z.right = T2

        z.height = 1 + max(self._get_height(z.left), self._get_height(z.right))
        y.height = 1 + max(self._get_height(y.left), self._get_height(y.right))

        return y

    def _get_height(self, node):
        if not node:
            return 0
        return node.height

    def _get_balance(self, node):
        if not node:
            return 0
        return self._get_height(node.left) - self._get_height(node.right)

    def display_tree(self):
        self._display_tree_helper(self.root, 0)

    def _display_tree_helper(self, node, space):
        if not node:
            return
        space += 3

        self._display_tree_helper(node.right, space)

        print()
        for _ in range(space):
            print(" ", end="")
        print(node.population)

        self._display_tree_helper(node.left, space)

    def print_top_x(self, count):
        rank = [1]
        self._print_top_x_helper(self.root, count, rank)

    def _print_top_x_helper(self, node, count, rank):
        if not node or rank[0] > count:
            return

        self._print_top_x_helper(node.right, count, rank)
        if rank[0] > count:
            return

        print(f"{rank[0]:4}. The zipcode {node.zipcode} has a population of {node.population}.")
        rank[0] += 1

        self._print_top_x_helper(node.left, count, rank)

    def print_least_x(self, count):
        rank = [1]
        self._print_least_x_helper(self.root, count, rank)

    def _print_least_x_helper(self, node, count, rank):
        if not node or rank[0] > count:
            return

        self._print_least_x_helper(node.left, count, rank)
        if rank[0] > count:
            return

        print(f"{rank[0]:4}. The zipcode {node.zipcode} has a population of {node.population}.")
        rank[0] += 1

        self._print_least_x_helper(node.right, count, rank)

def insert_from_csv(avl_tree, csv_file):
    current_dir = os.path.dirname(__file__)  # Get the directory of the current script
    csv_path = os.path.join(current_dir, csv_file)  # Create the absolute path to the CSV file
    
    with open(csv_path, newline='', encoding='utf-8-sig') as file:  # Use utf-8-sig encoding to handle BOM (Byte Order Mark)
        reader = csv.DictReader(file)
        for row in reader:
            population = int(row.get('population', -1))
            zipcode = int(row.get('zipcode', -1))

            if population == -1 or zipcode == -1:
                print("Warning: Missing population or zipcode value in row:", row)
                continue

            avl_tree.insert(population, zipcode)

if __name__ == "__main__":
    start_time = time.time()  # Start the timer
    
    avl_tree = AVLTree()
    insert_from_csv(avl_tree, 'population_by_zip_2010.csv')
    
    end_time = time.time()  # End the timer
    elapsed_time = end_time - start_time  # Calculate the elapsed time

    print("Displaying AVL Tree:")
    avl_tree.display_tree()

    print("\nTop 5 Zipcodes by Population:")
    avl_tree.print_top_x(5)

    print("\nLeast 5 Zipcodes by Population:")
    avl_tree.print_least_x(5)

    print(f"\nTime elapsed: {elapsed_time:.4f} seconds")  # Print the elapsed time with 4 decimal places
