# **Portfolio**
This repository showcases schoolwork and personal projects.

---

## **Featured Projects**

### 1. **Data Analysis with Python**
- **Tools:** Python, Pandas, CuDA, Matplotlib (and Weka)
- *Analyzed and contrasted predicitive models to grade pharmaceutical reviews.  Highlighting skills in data manipulation and statistical analysis.*
- *Applied machine learning algorithms to demonstrate their capacity to predict obesity levels given biometric and lifestyle information. Furthering skills in data analysis.*
- *Worked with team member to test and contrast predictive models for hard drug abuse that could be applied to discover at risk individuals based on psychological markers and lifestyle data.*

- ### 2. Game Development
- **Tools:** C#, Unity
- *Constructed mini games, procedural generation tests and more for skill development, created fleshed out platformer game that can be played in browser*

- ### 3. Data Structures and Misc. Work with Algorithms
- **Tools:** C++, Python
- *The red black tree is essentially a binary search tree that autobalances when new data is added*
- *The file implementing Huffman Compression allows users to compress a text file into a smaller, encoded file using a frequency-based binary tree*
- *The KNN file is classwork writing the K-Nearest Neighbors Classifier Algorithm from scratch*

### Repository Files
<ul>
  {% for folder in site.static_files %}
    {% assign folder_name = folder.path | split: "/" | first %}
    {% if folder_name != "." and folder_name != "" %}
      <li>
        <a href="{{ folder_name }}/">{{ folder_name }}</a>
      </li>
    {% endif %}
  {% endfor %}
</ul>
    

## **Contact**

I am currently seeking internships or entry-level opportunities in software development. Feel free to reach out:

- **Email:** [unavrgjoe@gmail.com](mailto:unavrgjoe@gmail.com)
- **LinkedIn:** [Joseph Gross](www.linkedin.com/in/joseph-gross-a5a07a347)
- **Phone:** (636) 485-9156
