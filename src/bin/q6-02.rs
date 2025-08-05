use std::{collections::HashMap, fs::File, io::{BufRead, BufReader}};

fn dfs(map: &HashMap<String, Vec<String>>, depth_map: &mut HashMap<i32, Vec<String>>, root: &str, depth: i32, path: &mut String) {
    if root == "@" {
        depth_map.entry(depth).or_default().push(path.to_string());
        return;
    }

    if let Some(children) = map.get(root) {
        for child in children {
            path.push(child.chars().next().unwrap());
            dfs(map, depth_map, child, depth + 1, path);
            path.truncate(path.len() - 1);
        }
    }
} 

fn main() {
    let reader = BufReader::new(File::open("data.txt").unwrap());
    let mut map: HashMap<String, Vec<String>> = HashMap::new();
    let mut depth_map: HashMap<i32, Vec<String>> = HashMap::new();

    for line in reader.lines() {
        let line = line.unwrap();

        let Some(pos) = line.find(':') else { panic!() };

        let parent = line[0..pos].to_string();

        let children: Vec<String> = line[pos+1..]
        .split(',')
        .map(|s| s.to_string())
        .collect();

        map.insert(parent, children);
    }

    let root = "RR";
    let mut path = String::from(root);

    dfs(&map, &mut depth_map, root, 0, &mut path);

    for vec in depth_map.into_values() {
        if vec.len() == 1 { print!("{}", vec[0]); }
    }

}