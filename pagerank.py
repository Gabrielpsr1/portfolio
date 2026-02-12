import os
import random
import re
import sys

DAMPING = 0.85
SAMPLES = 10000


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python pagerank.py corpus")
    corpus = crawl(sys.argv[1])
    ranks = sample_pagerank(corpus, DAMPING, SAMPLES)
    print(f"PageRank Results from Sampling (n = {SAMPLES})")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")
    ranks = iterate_pagerank(corpus, DAMPING)
    print(f"PageRank Results from Iteration")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")


def crawl(directory):
    """
    Parse a directory of HTML pages and check for links to other pages.
    Return a dictionary where each key is a page, and values are
    a list of all other pages in the corpus that are linked to by the page.
    """
    pages = dict()

    # Extract all links from HTML files
    for filename in os.listdir(directory):
        if not filename.endswith(".html"):
            continue
        with open(os.path.join(directory, filename)) as f:
            contents = f.read()
            links = re.findall(r"<a\s+(?:[^>]*?)href=\"([^\"]*)\"", contents)
            pages[filename] = set(links) - {filename}

    # Only include links to other pages in the corpus
    for filename in pages:
        pages[filename] = set(
            link for link in pages[filename]
            if link in pages
        )

    return pages


def transition_model(corpus, page, damping_factor):
    """
    Return a probability distribution over which page to visit next,
    given a current page.

    With probability `damping_factor`, choose a link at random
    linked to by `page`. With probability `1 - damping_factor`, choose
    a link at random chosen from all pages in the corpus.
    """
    transition_model = dict()
    random_number = random.random()
    pages = corpus.keys()
    N = len(corpus)
    links = corpus[page]

    if not links:
        # if a  page don't have links to others:
        prob = 1 / N
        for pg in pages:
            transition_model[pg] = prob 
    else:
        # divide the 1 - DAMPING by N
        prob = (1 - damping_factor) / N
        for pg in pages:
            transition_model[pg] = prob
        # divide de DAMPING by every possible link
        chance_random_surfer = damping_factor / len(links)
        for link in links:
            transition_model[link] += chance_random_surfer
    return transition_model


def normalize(probs):
    total = sum(probs.values())
    for key in probs:
        probs[key] /= total
    return probs


def generate_sample(corpus, page, damping_factor):
    # choose the next page based on the transition model
    random_number = random.random()
    tm = transition_model(corpus, page, damping_factor)
    aux = 0
    # loops in all prob values until they match the random number
    for key, value in tm.items():
        aux += value
        if random_number <= aux:
            return key
        

def sample_pagerank(corpus, damping_factor, n):
    """
    Return PageRank values for each page by sampling `n` pages
    according to transition model, starting with a page at random.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    # pick a random page
    page = random.choice(list(corpus.keys()))
    data = []
    data.append(page)

    for i in range(n):
        page = generate_sample(corpus, page, damping_factor)
        data.append(page)

    pages = corpus.keys()
    sample_pagerank = dict()
    # populate the dict
    for pg in pages:
        sample_pagerank[pg] = data.count(pg)

    return normalize(sample_pagerank)


def links(corpus, page):
    """
    returns all links that goes to a n page
    """
    links = []
    for key, value in corpus.items():
        if page in value:
            links.append(key)
    return links


def iterate_pagerank(corpus, damping_factor):
    """
    Return PageRank values for each page by iteratively updating
    PageRank values until convergence.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    # assigning each page a rank of 1 / N
    N = len(corpus)
    pages = corpus.keys()
    iterate_pagerank = dict()
    iterate_pagerank_aux = dict()
    for page in pages:
        iterate_pagerank[page] = 1 / N
        iterate_pagerank_aux[page] = 1

    loop = True
    while (loop):

        new_pagerank = iterate_pagerank.copy()
        for page in pages:
            # catch all the links
            incoming = links(corpus, page)

            # calculate 
            rank_sum = 0
            for i in incoming:
                # Número de links que SAEM de i
                num_links = len(corpus[i]) if corpus[i] else N
                rank_sum += iterate_pagerank[i] / num_links
            
            new_pagerank[page] = (1 - damping_factor) / N + damping_factor * rank_sum
        iterate_pagerank = new_pagerank.copy()

        # LOOP while no PageRank value changes by more than 0.001
        loop = False
        for page in pages:
            if abs(iterate_pagerank[page]-iterate_pagerank_aux[page]) > 0.001:
                loop = True
        iterate_pagerank_aux = iterate_pagerank.copy()

    return normalize(iterate_pagerank)


if __name__ == "__main__":
    main()
