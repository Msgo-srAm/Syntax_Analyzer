import sys
import os
import subprocess

def parse_production(line):   
    parts = line.strip().split('->')
    lhs = parts[0].strip()
    if len(parts) > 1:
        rhs = parts[1].strip().split()
    else:
        rhs = []
    return lhs, rhs

def visualize(input_file, output_file):
    if not os.path.exists(input_file):
        print(f"Error: Input file '{input_file}' not found.")
        return

    with open(input_file, 'r') as f:
        lines = f.readlines()

    productions = []
    for line in lines:
        if not line.strip(): continue
        lhs, rhs = parse_production(line)
        productions.append((lhs, rhs))

    if not productions:
        print("No productions found.")
        return

    node_count = 0
    def new_node(label):
        nonlocal node_count
        node_count += 1
        return {'id': str(node_count), 'label': label, 'children': []}

    # The first production determines the root
    root_lhs, _ = productions[0]
    root = new_node(root_lhs)
    leaves = [root]

    for i, (lhs, rhs) in enumerate(productions):
        # Find the right-most leaf that has label == lhs
        target_node = None
        target_index = -1
        
        for idx in range(len(leaves) - 1, -1, -1):
            if leaves[idx]['label'] == lhs:
                target_node = leaves[idx]
                target_index = idx
                break
        
        if target_node is None:
            print(f"Warning: Could not find leaf for non-terminal '{lhs}' at step {i+1}. Skipping.")
            continue

        new_leaves = []
        # If rhs is empty or epsilon, we might want to represent it
        if not rhs or (len(rhs) == 1 and rhs[0] == 'epsilon'):
             child = new_node('epsilon')
             target_node['children'].append(child)
             # epsilon is a terminal, so it stays in leaves? 
             # Or we just don't add it to leaves if we don't want to expand it.
             # But for visualization, it's a leaf.
             new_leaves.append(child)
        else:
            for symbol in rhs:
                child = new_node(symbol)
                target_node['children'].append(child)
                new_leaves.append(child)
            
        # Replace the expanded node with its children in the leaves list
        leaves[target_index:target_index+1] = new_leaves

    # Generate GV file
    gv_file = output_file if output_file.endswith('.gv') else output_file + '.gv'
    
    with open(gv_file, 'w') as f:
        f.write("digraph G {\n")
        f.write("    node [shape=box];\n") 
        
        # BFS to write nodes and edges
        stack = [root]
        while stack:
            node = stack.pop(0) 
            f.write(f'    node{node["id"]} [label="{node["label"]}"];\n')
            for child in node['children']:
                f.write(f'    node{node["id"]} -> node{child["id"]};\n')
                stack.append(child)
        
        f.write("}\n")
    
    print(f"Graphviz file generated: {gv_file}")
    
    # Try to render PNG
    png_file = gv_file.replace('.gv', '.png')
    try:
        # Check if dot is available
        subprocess.run(['dot', '-V'], check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        subprocess.run(['dot', '-Tpng', gv_file, '-o', png_file], check=True)
        print(f"Image generated: {png_file}")
    except (subprocess.CalledProcessError, FileNotFoundError):
        print("Graphviz 'dot' command not found or failed. Please install Graphviz to generate PNG.")
        print(f"You can manually render the .gv file using: dot -Tpng {gv_file} -o {png_file}")

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python visualize.py <input_file> [output_file_base]")
    else:
        input_file = sys.argv[1]
        output_file = sys.argv[2] if len(sys.argv) > 2 else os.path.splitext(input_file)[0]
        visualize(input_file, output_file)
