#!/usr/bin/env python3
"""Plot the 5th-degree polynomial from coefficients written by main.cpp."""
from __future__ import annotations

import argparse
from pathlib import Path
import sys


def read_coefficients(path: Path) -> list[float]:
    """Read lines of the form 'a<k>: <value>' and return [a0, a1, ...]."""
    coef: dict[int, float] = {}
    with path.open(encoding="utf-8") as stream:
        for number, line in enumerate(stream, start=1):
            line = line.strip()
            if not line:
                continue
            name, sep, value = line.partition(":")
            if not sep or not name.startswith("a"):
                raise ValueError(f"Malformed line {number}: {line!r}")
            coef[int(name[1:])] = float(value)
    if sorted(coef) != list(range(len(coef))) or not coef:
        raise ValueError("Coefficients must be a0..aN without gaps")
    return [coef[k] for k in range(len(coef))]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=Path, help="coefficients file written by main.cpp")
    parser.add_argument("--output", required=True, type=Path, help="destination .png or .pdf")
    parser.add_argument("--overwrite", action="store_true")
    args = parser.parse_args()
    try:
        if args.output.suffix.lower() not in {".png", ".pdf"}:
            raise ValueError("Output must end in .png or .pdf")
        if args.output.exists() and not args.overwrite:
            raise ValueError("Plot exists; choose a new name or pass --overwrite")
        if not args.output.parent.is_dir():
            raise ValueError("Output parent directory does not exist")

        a = read_coefficients(args.input)

        import numpy as np
        import matplotlib
        matplotlib.use("Agg")
        import matplotlib.pyplot as plt

        x = np.linspace(0.0, 3.0, 400)
        f = sum(a[i] * x**i for i in range(len(a)))

        # węzły i wartości z warunków (2)-(7): f(0)=0, f(1)=1, f(2)=0, f(3)=-1
        nodes_x = [0, 1, 2, 3]
        nodes_y = [0, 1, 0, -1]

        fig, ax = plt.subplots(figsize=(6, 4.2))
        ax.plot(x, f, "k-", label="f(x)")
        ax.axhline(0, color="blue", lw=0.8)
        ax.plot(nodes_x, nodes_y, "ro", label="nodes")
        ax.set(xlabel="x", ylabel="f(x)", xlim=(0, 3))
        ax.grid(True, alpha=0.3)
        ax.legend()
        fig.tight_layout()
        fig.savefig(args.output, dpi=180)
        plt.close(fig)
        print(f"Read {len(a)} coefficients from {args.input}; saved {args.output}")
        return 0
    except (OSError, ValueError, ImportError) as exc:
        print(f"Plot error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())