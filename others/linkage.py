from collections import defaultdict

ARCA = [
        {
            "type": "EOA",
            "sym": "AAPL",
            "seq": 1,
            "oid": "ARCA-1",
            "rid": "XXX-1",
        },
        {
            "type": "EOR",
            "seq": 2,
            "oid": "ARCA-1",
            "rid": "BD-1",
        },
        {
            "type": "EMR",
            "seq": 3,
            "oid": "ARCA-2",
            "ooid": "ARCA-1",
            "rid": "BD-2",
            "orid": "BD-1"
        },
        {
            "type": "EOA",
            "sym": "MSFT",
            "seq": 4,
            "oid": "ARCA-3",
            "rid": "XXX-3",
        },
        {
            "type": "EOR",
            "seq": 5,
            "oid": "ARCA-3",
            "rid": "BD-3",
        },
        {
            "type": "EOM",
            "seq": 6,
            "oid": "ARCA-2",
            "ooid": "ARCA-1",
            "rid": "XXX-2",
            "orid": "XXX-1"
        },
        {
            "type": "EOF",
            "seq": 7,
            "oid": "ARCA-2",
            "rid": "BD-2",
        },
        {
            "type": "EOF",
            "seq": 8,
            "oid": "ARCA-3",
            "rid": "BD-3",
        }
]


BD = [
        {
            "type": "EOA",
            "sym": "AAPL",
            "seq": 1,
            "oid": "BD-1",
            "rid": "ARCA-1",
        },
        {
            "type": "EOR",
            "seq": 2,
            "oid": "BD-1",
            "rid": "NASD-1",
        },
        {
            "type": "EMR",
            "seq": 3,
            "oid": "BD-2",
            "ooid": "BD-1",
            "rid": "NASD-2",
            "orid": "NASD-1"
        },
        {
            "type": "EOM",
            "seq": 4,
            "oid": "BD-2",
            "ooid": "BD-1",
            "rid": "ARCA-2",
            "orid": "ARCA-1"
        },
        {
            "type": "EOF",
            "seq": 5,
            "oid": "BD-2",
            "rid": "NASD-2",
        },
        {
            "type": "EOA",
            "sym": "MSFT",
            "seq": 6,
            "oid": "BD-3",
            "rid": "ARCA-3",
        },
        {
            "type": "EOR",
            "seq": 7,
            "oid": "BD-3",
            "rid": "NASD-3",
        },
        {
            "type": "EOF",
            "seq": 8,
            "oid": "BD-3",
            "rid": "NASD-3",
        },
]


NASD = [
        {
            "type": "EOA",
            "sym": "AAPL",
            "seq": 1,
            "oid": "NASD-1",
            "rid": "BD-1",
        },
        {
            "type": "EOM",
            "seq": 2,
            "oid": "NASD-2",
            "ooid": "NASD-1",
            "rid": "BD-2",
            "orid": "BD-1"
        },
        {
            "type": "EOT",
            "seq": 3,
            "tid": "NASD-T-1",
            "boid": "NASD-2",
            "soid": "NASD-21"
        },
        {
            "type": "EOA",
            "sym": "AAPL",
            "seq": 4,
            "oid": "NASD-3",
            "rid": "BD-3",
        },
        {
            "type": "EOT",
            "seq": 5,
            "tid": "NASD-T-3",
            "boid": "NASD-3",
            "soid": "NASD-23"
        },
]


class Linkage(object):
    def __init__(self, parent, child):
        self.parent = parent
        self.child = child


class Report(object):
    def __init__(self, events, global_order_chain):
        self.order_book = defaultdict(list)
        self.internal_order_link = {}
        self.global_order_chain = global_order_chain
        for e in events:
            oid = e['oid'] if 'oid' in e else e['boid']
            type = e['type']
            self.order_book[oid].append(e)
            if 'ooid' in e:
                self.internal_order_link[oid] = e['ooid']
            else:
                if oid not in self.internal_order_link:
                    self.internal_order_link[oid] = oid
            if type == 'EOA':
                self.global_order_chain.setdefault(oid, Linkage(None, None)).parent = e['rid']
            if type == 'EOR':
                self.global_order_chain.setdefault(oid, Linkage(None, None)).child = e['rid']

        # eliminate chains
        for key in self.internal_order_link:
            if key != self.internal_order_link[key]:
                parent = self._find_parent(key)
                self.order_book[parent] += self.order_book.pop(key)

    def _find_parent(self, key):
        if key not in self.internal_order_link:
            raise KeyError("Unknown key %s" % (key))
        else:
            value = self.internal_order_link[key]
            return key if key == value else self._find_parent(value)


class Ingestor(object):
    def __init__(self, global_order_chain):
        self.reports = {}
        self.global_order_chain = global_order_chain

    def report(self, id, events):
        self.reports[id] = Report(events, self.global_order_chain)

    def dump(self):
        return self.reports


class Normalizer(object):
    def __init__(self, reports, global_order_chain):
        self.reports = reports
        self.global_order_chain = global_order_chain
        self.linkage = self._link()

    def _link(self):
        chains = self.global_order_chain.copy()
        linkage = {}
        i = 1
        while len(chains) != 0:
            key = chains.keys()[0]
            parents = []
            self._get_parent(chains, key, parents)
            children = []
            self._get_child(chains, key, children)
            a_linkage = parents + [key] + children
            # remove all items in the linkage in the chain
            for e in a_linkage:
                if e in chains:
                    chains.pop(e)
            linkage[i] = ':'.join([l for l in a_linkage if l is not None])
            i += 1
        # we can of course link each item in the linkage to their corresponding
        # order chain in their report, but for brevity, we are only showing
        # the linkage itself
        return linkage

    def _get_parent(self, chains, key, parents):
        if key in chains:
            parent = chains[key].parent
            self._get_parent(chains, parent, parents)
            parents.append(parent)

    def _get_child(self, chains, key, children):
        if key in chains:
            child = chains[key].child
            children.append(child)
            self._get_child(chains, child, children)


def main():
    global_order_chain = {}
    ingestor = Ingestor(global_order_chain)
    ingestor.report('NASD', NASD)
    ingestor.report('BD', BD)
    ingestor.report('ARCA', ARCA)
    # print(global_order_chain)

    normalizer = Normalizer(ingestor.dump(), global_order_chain)
    print(normalizer.linkage)

if __name__ == "__main__":
    main()
