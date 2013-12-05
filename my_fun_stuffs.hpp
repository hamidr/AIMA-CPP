
template < 
    typename T,
    typename F,
    typename Rf = typename std::result_of<F(T)>::type,
    typename R = Node<typename std::enable_if<!std::is_void<Rf>::value, Rf>::type>
    >
R map(const Node<T> &node, const F &f)
{
    R r(f(node.getValue()));
    for( const auto &l : node.getLeafs() ) 
            r.addLeaf(map(*l, f));
    return r;
}

 
template <
    typename T,
    typename F,
    typename Rf = typename std::result_of<F(T)>::type
    >
typename std::enable_if<std::is_void<Rf>::value,void>::type 
map(const Node<T> &node, const F &f)
{
    f(node.getValue());

    for( const auto &l : node.getLeafs() ) 
            map(*l, f);
}

template < typename T, typename L >
void toSequencial( const Node<T> &n, L &seq )
{
    auto itr = seq.begin();
    map(n, [&](const T &e) {
        seq.emplace(itr, e);
        itr = seq.end();
    });
}

template < typename T, typename F >
void mapOnce( const Node<T> &n, const F &f)
{
    std::set<Node<T>*> uns;
    mapOnce(n,f,uns);
}


template <
    typename T,
    typename F,
    typename Rf = typename std::result_of<F(T)>::type
    >
typename std::enable_if<std::is_void<Rf>::value,void>::type 
mapOnce(const Node<T> &node, const F &f, std::set<Node<T>*> &unions)
{
    if ( unions.insert((Node<T>*)&node).second == false )
        return;

    f(node.getValue());
    for( auto &l : node.getLeafs() ) 
        mapOnce(*l, f, unions);
}

