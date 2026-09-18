# Linux Platform

## Purpose

This directory contains the Linux-specific implementation of NetShield's platform layer.

The platform layer keeps operating-system-specific behavior separate from the generic networking and tunnel components. Code that depends on Linux should live here rather than leaking into platform-independent parts of the project.

## Responsibilities

- `network_manager` manages the Linux networking lifecycle.
- Linux kernel and networking APIs will eventually be integrated through this layer.
- Linux-specific behavior should remain isolated from generic networking and tunnel components.

## Current State

The current implementation is only a lifecycle stub. It provides the structure for the Linux platform layer, but does not yet implement actual Linux networking functionality.

Real Linux networking support will be added here as the project develops.